
#include "Image.h"
#include <iostream>
#include <OpenImageIO/imageio.h>
#include <cstring>

Image::Image(unsigned int _width, unsigned int _height, unsigned int _channels)
{
    m_width=_width;
    m_height=_height;
    m_channels=_channels;
    m_pixels = std::make_unique<unsigned char []>(m_width*m_height*m_channels);
}

Image::Image(const Image &_c)
{
    m_width=_c.m_width;
    m_height=_c.m_height;
    m_channels=_c.m_channels;
    m_pixels = std::make_unique<unsigned char []>(m_width*m_height*m_channels);
    memcpy(m_pixels.get(),_c.m_pixels.get(),m_width*m_height*m_channels);
}

void Image::Draw_Line(unsigned int _x0, unsigned int _y0, unsigned int _x1, unsigned int _y1)
{
    int _dx = _x1 - _x0;
    int _dy = _y1 - _y0;
    int _D = 2*_dy - _dx;
    int _y = _y0;

     for(int x =_x0; x<_x1; ++x)
     {
        setPixel(x,_y,255,0,0);
        if(_D > 0)
        {
          _y = _y + 1;
          _D = _D - 2*_dx;
        }
       _D = _D + 2*_dy;
     }
}

void Image::setPixel(unsigned int _x, unsigned int _y, unsigned char _r, unsigned char _g, unsigned _b)
{

    size_t index=(m_width*m_channels*_y)+m_channels*_x;
    m_pixels[index]=_r;
    m_pixels[index+1]=_g;
    m_pixels[index+2]=_b;

}


void Image::getPixel(unsigned int _x, unsigned int _y, unsigned char &o_r, unsigned char &o_g, unsigned char &o_b)
{
 size_t index=(m_width*m_channels*_y)+m_channels*_x;
 o_r=m_pixels[index];
 o_g=m_pixels[index+1];
 o_b=m_pixels[index+2];
}

bool Image::write(const std::string &_fname)
{
    using namespace OIIO;
    std::unique_ptr<ImageOutput> out = ImageOutput::create (_fname);
    if(!out)
    {
        return false;
    }
    bool success;
    ImageSpec spec (m_width,m_height,m_channels, TypeDesc::UINT8);
    success=out->open(_fname,spec);
    success=out->write_image(TypeDesc::UINT8,m_pixels.get());
    success=out->close();
    return success;
}

void Image::clearColour(unsigned char _r, unsigned char _g, unsigned char _b)
{
    for(size_t y=0; y<m_height; ++y)
    {
        for(size_t x=0; x<m_width; ++x)
        {
            setPixel(x,y,_r,_g,_b);
        }
    }
}



unsigned char * Image::pixels()
{
    return m_pixels.get();
}


unsigned int Image::width() const noexcept
{
    return m_width;
}

unsigned int Image::height() const noexcept
{
    return m_height;
}


unsigned int Image::channels() const noexcept
{
    return m_channels;
}



int main()
{
    constexpr size_t width=150;
    constexpr size_t height=150;

    std::cout<<"Image Sequence\n";
    Image myImage(width,height);

    for(size_t current=0; current<width; ++current)
    {
        myImage.clearColour(current,255,255);

        myImage.Draw_Line(100,0,20,100);

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






