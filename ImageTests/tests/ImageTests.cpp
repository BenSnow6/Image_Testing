
#include "Image.h"
#include <gtest/gtest.h>
using namespace ::testing;
// for more details on gtest see here https://github.com/google/googletest/blob/master/googletest/docs/primer.md
// my lecture https://nccastaff.bournemouth.ac.uk/jmacey/PP/slides/testing/slides.html#/
TEST(Image, defaultCtor)
{
    Image i;
    EXPECT_EQ(i.width(),0);
    EXPECT_EQ(i.height(),0);
    EXPECT_EQ(i.channels(),3);
    EXPECT_EQ(i.pixels(),nullptr);
}


TEST(Image,userCtor)
{
    Image i(100,100);
    EXPECT_EQ(i.width(),100);
    EXPECT_EQ(i.height(),100);
    EXPECT_EQ(i.channels(),3);
    EXPECT_NE(i.pixels(),nullptr);
}


TEST(Image,setPixel)
{
    Image i(100,100);
    i.setPixel(0,0,255,0,0); // set first pixel to red
    unsigned char r,g,b;
    i.getPixel(0,0,r,g,b);
    EXPECT_EQ(r,255);
    EXPECT_EQ(g,0);
    EXPECT_EQ(b,0);

    i.setPixel(10,10,255,128,12); // set first pixel to red
    i.getPixel(10,10,r,g,b);
    EXPECT_EQ(r,255);
    EXPECT_EQ(g,128);
    EXPECT_EQ(b,12);
}

TEST(Image,writeFile)
{
    Image i(100,100);
    i.setPixel(0,0,255,0,0);
    i.setPixel(1,0,0,255,0);
    i.setPixel(2,0,0,0,255);
    EXPECT_TRUE(i.write("test.png"));
}


TEST(Image,clearColour)
{
    Image i(100,100);
    i.clearColour(128,128,128);
    i.setPixel(0,0,255,0,0);
    i.setPixel(1,0,0,255,0);
    i.setPixel(2,0,0,0,255);
    EXPECT_TRUE(i.write("test.png"));

}



TEST(Image,copyCtor)
{
    Image i(100,100);
    i.clearColour(128,128,128);
    i.setPixel(0,0,255,0,0);
    i.setPixel(1,0,0,255,0);
    i.setPixel(2,0,0,0,255);

    Image image2=i;
    unsigned char r,g,b;
    i.getPixel(0,0,r,g,b);
    EXPECT_EQ(r,255);
    EXPECT_EQ(g,0);
    EXPECT_EQ(b,0);
}

TEST(Image, DrawLine)
{
    Image i(100,100);
    //need to check that the colour written on first point of line is red
    unsigned char r,g,b;
    i.Draw_Line(0,0,0,100);
    i.getPixel(0,0,r,g,b);
    EXPECT_EQ(r,255);
    EXPECT_EQ(g,0);
    EXPECT_EQ(b,0);

    Image image2(100,100);
    //check that all pixels along horizontal line are the colour written on first point of line is red
    image2.Draw_Line(0,0,0,100);
    for(int j = 0; j<100; ++j)
    {
        image2.getPixel(0,j,r,g,b);
        EXPECT_EQ(r,255);
        EXPECT_EQ(g,0);
        EXPECT_EQ(b,0);
    }
}



