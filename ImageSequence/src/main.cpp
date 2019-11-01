#include <iostream>
#include <cstdlib>
#include "Image.h"
int main()
{
    constexpr size_t width=150;
    constexpr size_t height=150;

    std::cout<<"Image Sequence\n";
    Image myImage(width,height);

    for(size_t current=0; current<width; ++current)
    {
        myImage.clearColour(current,255,255);

        myImage.Draw_Line(0,0,0,100);

//        for(size_t x=0; x<=current; ++x)
//        {
//            myImage.setPixel(x,x,255,0,0);

//        }




        char fname[100];
        sprintf(fname,"/home/s5222107/Desktop/ASE/ASELectureCode/Image_drawing/Image_Testing/ImageSequence/images/test.%04ld.png", current); //%04ld makes sure the file has 4 numbers in the filename e.g. 0056 for image 56
        std::cout<<"Writing file"<<fname<<"\n";
        myImage.write(fname);

    }
    return EXIT_SUCCESS;
}
