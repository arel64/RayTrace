#ifndef SAFEQUEUE
#define SAFEQUEUE

#include <vector>
#include <cstdint>
#include <mutex>
#include <atomic>

template <class T> 
class SafeQueue{
    public:
        SafeQueue(uint32_t size):capacity(size),head(0),tail(-1),size(0){dataArr = new T[size];};
        ~SafeQueue(){delete dataArr;};


        int64_t getSize(){
            return size;
        }
        bool isEmpty(){
            assert(size>=0);
            return (getSize() <= 0);
        }
        bool isFull(){
            assert(size<=capacity);
            return (getSize() >= capacity);
        }
        void enqueue(T data){
            // check for queue overflow
            
            if (isFull())
            {
                return;
            }
            endeMutex.lock();
                tail = (tail + 1) % capacity;
                dataArr[tail] = data;
                size++;
            endeMutex.unlock();
        }
        T dequeue(){
            // check for queue underflow
            
            if (isEmpty())
            {
                //Underflow
                return T();
            }
            endeMutex.lock();
                T x = dataArr[head];
            
                head = (head + 1) % capacity;
                size--;
            endeMutex.unlock();
            return x;
        }
    public:
        std::mutex endeMutex,sizeMutex;
        T* dataArr;
        int32_t head;
        int32_t tail;
        std::atomic<int64_t> size;
        const uint32_t capacity;
};
#endif