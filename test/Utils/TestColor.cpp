#include <gtest\gtest.h>
#include <h\Utils\Color.hpp>
#include <SFML/Graphics.hpp>

TEST(testcolor, SFMLConversion) {
    Color c = Color(0.5,0.2,0.03);
    sf::Color d = c.toSFMLColor();
    EXPECT_NEAR(c.r*255, d.r, 1);
    EXPECT_NEAR(c.g*255, d.g, 1);
    EXPECT_NEAR(c.b*255, d.b, 1);
    EXPECT_NEAR(c.alpha*255, d.a, 1);

}
TEST(testcolor, CLAMP) {
    Color c = Color(1.5,-0.2,1.03,953);
    EXPECT_NEAR(c.r, 1, 0.01f);
    EXPECT_NEAR(c.g, 0, 0.01f);
    EXPECT_NEAR(c.b, 1, 0.01f);
    EXPECT_NEAR(c.alpha, 1, 953);
}

TEST(testcolor, OPERATORS) {
    Color colorA = Color(0.5f,0.2f,1,0.2f);
    Color colorB = Color(0.8f,0,1,0.2f);

    Color add = colorA + colorB;
    Color multiply = colorA * colorB;
    Color multplyScalar = colorA*0.5;
    Color DevideScalar = colorA/0.5;
    
    EXPECT_NEAR(add.r, 1, 0.01f);
    EXPECT_NEAR(add.g, 0.2, 0.01f);
    EXPECT_NEAR(add.b, 1, 0.01f);
    EXPECT_NEAR(add.alpha, 0.4, 0.01f);
    
    EXPECT_NEAR(multiply.r, 0.4f, 0.01f);
    EXPECT_NEAR(multiply.g, 0, 0.01f);
    EXPECT_NEAR(multiply.b, 1, 0.01f);
    EXPECT_NEAR(multiply.alpha, 0.04f, 0.01f);
    
    EXPECT_NEAR(multplyScalar.r, 0.25, 0.01f);
    EXPECT_NEAR(multplyScalar.g, 0.1, 0.01f);
    EXPECT_NEAR(multplyScalar.b, 0.5, 0.01f);
    EXPECT_NEAR(multplyScalar.alpha, 0.1, 0.01f);
    
    EXPECT_NEAR(DevideScalar.r, 1, 0.01f);
    EXPECT_NEAR(DevideScalar.g, 0.4, 0.01f);
    EXPECT_NEAR(DevideScalar.b, 1, 0.01f);
    EXPECT_NEAR(DevideScalar.alpha, 0.4, 0.01f);

}
TEST(testcolor, ASSSIGNMENT) {
    Color colorA = Color(0.5,0.2,1,0.2);
    Color colorB = colorA;

    EXPECT_NEAR(colorB.r, 0.5, 0.01f);
    EXPECT_NEAR(colorB.g, 0.2, 0.01f);
    EXPECT_NEAR(colorB.b, 1, 0.01f);
    EXPECT_NEAR(colorB.alpha, 0.2, 0.01f);

}