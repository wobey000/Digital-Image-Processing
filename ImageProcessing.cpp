#include "ImageProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


ImageProcessing::ImageProcessing(const char* _inImgName, const char* _outImgName, int* _height, int* _width, int* _bitDepth, unsigned char*  _header, unsigned char* _colorTable, unsigned char* _inBuf, unsigned char* outBuf)
{
    // Constructor
    inImgName = _inImgName; 
    outimgName = _outImgName; 
    height = _height; 
    width = _width; 
    bitDepth = _bitDepth; 
    header = _header; colorTable = _colorTable; 
    inBuf = _inBuf; 
    _outBuf = outBuf;

}

ImageProcessing::~ImageProcessing()
{
    // Destructor
}

void ImageProcessing::readImage()
{
    int i;
    FILE* streamIn; 
    streamIn = fopen(inImgName, "rb");
    if(streamIn == (FILE *)0)
    {
        std::cout << "Unable to open file. Maybe file doesn't exist buddy?" << std::endl; 
        exit(0); 
    }

    for(i = 0; i < BMP_HEADER_SIZE; i++)
    {
        header[i] = getc(streamIn); 
    }

    *width = *(int *)&header[18]; // reads width 
    *height = *(int *)&header[22]; // reads height 
    *bitDepth = *(int *)&header[28]; // reads bitDepth

    if(*bitDepth <= 8)
    {
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn); 
    }

    fread(inBuf, sizeof(unsigned char), _512by512_IMG_SIZE, streamIn);

    fclose(streamIn);
}

/*
flow: 
readImage() reads the image
then we will have some intermediate process (filtering, sharening, etc)
finally we will writeImage() and create a new file after all the processing is done (so we can see what we did)
*/


void ImageProcessing::writeImage()
{
    FILE* fo = fopen(outimgName, "wb"); 
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fo); // write from header array to fo 

    //checking 
    if(*bitDepth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fo); 
    }

    fwrite(_outBuf, sizeof(unsigned char), _512by512_IMG_SIZE, fo); 
    fclose(fo); 
}

void ImageProcessing::copyImage(unsigned char* _srcBuf, unsigned char* _desBuf, int bufSize)
{
    //duplicate of image data
    for(int i = 0; i < bufSize; i++)
    {
        _desBuf[i] = _srcBuf[i]; 
    }
}

void ImageProcessing::BrightnessUp(unsigned char* _inputImgData, unsigned char* _outImgData, int imgSize, int brightness)
{
    for(int i = 0; i < imgSize; i++)
    {
        int temp = _inputImgData[i] + brightness;

        // truncation (0-255) check 
        // remember to do the normalization equation for a more sophisticated implementation
        _outImgData[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp; 
    }
}

void ImageProcessing::BrightnessDown(unsigned char* _inputImgData, unsigned char* _outImgData, int imgSize, int darkness)
{
    for(int i = 0; i < imgSize; i++)
    {
        int temp = _inputImgData[i] - darkness;

        // truncation (0-255) check 
        // remember to do the normalization equation for a more sophisticated implementation
        _outImgData[i] = (temp < MIN_COLOR) ? MIN_COLOR : temp; 
    }
}

void ImageProcessing::ComputeHistogram(unsigned char* _imgData, int imgRows, int imgCols, float hist[])
{
    FILE *fptr;
    fptr = fopen("image_his.txt", "w"); 

    int x,y,i,j; 
    long int ihist[256], sum; 
    for(i = 0; i <=255; i++)
    {
        ihist[i] = 0; // yes I know this is ugly. I'll update it with modern C++ stuff later
    }

    sum = 0; 
    for(y = 0; y < imgRows; y++)
    {
        for(x = 0; i < imgCols; x++)
        {
            j = (*_imgData + x + y *imgCols);
            ihist[j] = ihist[j] + 1;
            sum = sum + 1;
        }
    }
    for(i = 0; i <= 255; i++)
    {
        hist[i] = (float)ihist[i] / (float)sum; // storing the output
    }

    for(i = 0; i <= 255; i++ )
    {
        fprintf(fptr, "\n%f", hist[i]); // write output to file 
    }

    fclose(fptr); 
}