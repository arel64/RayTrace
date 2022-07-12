#include <array>
#include <chrono>
#include <cstddef>
#include <gtest/gtest.h>
#include <h/Utils/SafeQueue.hpp>
#include <h/Render/PixelCluster.hpp>
#include <cstdint>
#include <stdint.h>
#include <thread>
#include <atomic>
#include <mutex>

using namespace std::chrono_literals;

TEST(testSafeQueue, basicIO) {
    uint16_t capacity = 1000;
    SafeQueue<PixelCluster>* queue= new SafeQueue<PixelCluster>(capacity);
    ASSERT_TRUE(queue->capacity==capacity);
    ASSERT_TRUE(queue->getSize()==0);
    auto a = PixelCluster(1,2,200,120,nullptr);
    auto b = PixelCluster(1,2,500,120,nullptr);
    queue->enqueue(a);
    queue->enqueue(a);
    queue->enqueue(b);
    ASSERT_TRUE(queue->dequeue().size.x==200);
    queue->dequeue();
    queue->dequeue();
    ASSERT_TRUE(queue->isEmpty());
    ASSERT_FALSE(queue->isFull());
    ASSERT_TRUE(queue->getSize()==0);
    delete queue;
}
TEST(testSafeQueue, threadedIO) {
    uint16_t capacity = 10000;
    
    std::atomic<bool> killEnqueue(false);
    std::atomic<bool> killDequeue(false);
    std::mutex timeoutMtx;
    std::condition_variable wakeVar;

    auto testQueueTime  =2000ms;
    auto testTimeoutSec  = 2100ms;


    SafeQueue<PixelCluster>* queue= new SafeQueue<PixelCluster>(capacity);
    auto a = PixelCluster(1,2,200,120,nullptr);
    auto b = PixelCluster(1,2,500,120,nullptr);
    

    //Start TestTimeout
    std::thread timeoutThread([&testTimeoutSec,&timeoutMtx,&wakeVar](){

        std::unique_lock<std::mutex>lock(timeoutMtx);
        auto now = std::chrono::system_clock::now();
        if(wakeVar.wait_until(lock,now + testTimeoutSec)==std::cv_status::timeout){
            //Timeout :(
            ASSERT_TRUE(false);
        }
    });
    

    std::thread inserterThread([&killEnqueue,a,b,&queue](){
        while(!killEnqueue)
            queue->enqueue(queue->getSize()%2==0?a:b);
    });
    std::thread removerThread([&killDequeue,&queue](){
        while(!killDequeue)
            queue->dequeue();
    });

    
    //Give threads some time
    std::this_thread::sleep_for(testQueueTime);
    killEnqueue =true;
    inserterThread.join();

    //Wait for queue to empty 
    while(!queue->isEmpty());

    //Stop threads
    killDequeue = true;
    wakeVar.notify_all();
    removerThread.join();
    timeoutThread.join();

    ASSERT_TRUE(queue->isEmpty());
    delete queue;
}
TEST(testSafeQueue, performanceTest4Cores) {
    if(std::thread::hardware_concurrency() < 4){
        GTEST_SKIP();
    }
    uint16_t capacity = 50000;
    auto insertElementTime = 6ns;
    auto removeElementTime = 6ns;

    SafeQueue<PixelCluster>* queue= new SafeQueue<PixelCluster>(capacity);
    auto a = PixelCluster(1,2,200,120,nullptr);
    auto b = PixelCluster(1,2,500,120,nullptr);

    auto startTime = std::chrono::steady_clock::now();
    
    std::array<std::thread,4> threads;
    for( auto& thread: threads){
        thread = std::thread([a,b,&queue]()
            {
                while(!queue->isFull())
                    queue->enqueue(queue->getSize()%2==0?a:b);
            }
        );
    }
    auto endEnqueue = std::chrono::steady_clock::now();
    auto timePassed = std::chrono::duration_cast<std::chrono::nanoseconds>(endEnqueue-startTime);
    EXPECT_LE(timePassed, insertElementTime*capacity);
    for( auto& thread: threads){
        thread.join();
    }


    startTime = std::chrono::steady_clock::now();
    for( auto& thread: threads){
        thread = std::thread([&queue]()
            {
                while(!queue->isEmpty())
                    queue->dequeue();
            }
        );
    }
    auto endDequeue = std::chrono::steady_clock::now();
    timePassed = std::chrono::duration_cast<std::chrono::nanoseconds>(endEnqueue-startTime);

    EXPECT_LE(timePassed, removeElementTime*capacity);
    for( auto& thread: threads){
        thread.join();
    }

    delete queue;
}
