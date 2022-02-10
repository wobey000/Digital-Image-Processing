#include <iostream> 
#include "ImageProcessing.h"

int main()
{
    //Test
    int imgWidth;
    int imgHeight; 
    int imgBitDepth; 
    unsigned char imgHeader[BMP_HEADER_SIZE]; 
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE]; 
    unsigned char imgInBuffer[_512by512_IMG_SIZE]; 
    unsigned char imgOutBuffer[_512by512_IMG_SIZE]; 

    const char imgName[] = "man.bmp"; 
    const char newImgName[] = "man_copy.bmp"; 

    ImageProcessing* myImage = new ImageProcessing(imgName, newImgName, &imgHeight, &imgWidth, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgInBuffer[0], &imgOutBuffer[0]);
    myImage->readImage();
    myImage->copyImage(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE); 
    myImage->writeImage(); 

    std::cout << "Good Job buddy :) " << std::endl; 
    std::cout << "Image Height: " << imgHeight << std::endl; 
    std::cout << "Image Width : " << imgWidth << std::endl; 
    return 0 ;
}