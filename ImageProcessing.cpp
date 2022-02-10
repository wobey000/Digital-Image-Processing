#include "ImageProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


ImageProcessing::ImageProcessing(const char* _inImgName, const char* _outImgName, int* _height, int* _width, int* _bitDepth, unsigned char*  _header, unsigned char* _colorTable, unsigned char* _inBuf, unsigned char* _outBuf)
{
    // Constructor
    inImgName = _inImgName; 
    outimgName = _outImgName; 
    height = _height; 
    width = _width; 
    bitDepth = _bitDepth; 
    header = _header; colorTable = _colorTable; 
    inBuf = _inBuf; 
    outBuf = _outBuf;

}

void ImageProcessing::readImage()
{
    int i;
    FILE* streamIn; 
    streamIn = fopen(inImgName, "rb");
    if(streamIn == (FILE *)0)
    [
        std::cout << "Unable to open file. Maybe file doesn't exist buddy?" << std::endl; 
        exit(0); 
    ]

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

    fwrite(outBuf, sizeof(unsigned char), _512by512_IMG_SIZE, fo); 
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



ImageProcessing::~ImageProcessing()
{
    // Destructor
}