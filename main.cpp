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

    // histrogram testing 
    float imgHist[NO_OF_GRAYLEVELS];

    const char imgName[] = "images/man.bmp"; 
    const char newImgName[] = "images/man_LD_RDIR.bmp" /*"images/blank.bmp"*/ ; // blank image since we're only looking at the .txt 

    ImageProcessing* myImage = new ImageProcessing(imgName, newImgName, &imgHeight, &imgWidth, &imgBitDepth, &imgHeader[0], &imgColorTable[0], &imgInBuffer[0], &imgOutBuffer[0]);
    myImage->readImage();
    //myImage->copyImage(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE); 
    //myImage->BrightnessUp(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 100);
    //myImage->BrightnessDown(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE, 100);
    //myImage->writeImage(); 
    //myImage->ComputeHistogram(imgInBuffer, imgHeight, imgWidth, imgHist);
    //myImage->equalizeHistogram(imgInBuffer, imgOutBuffer, imgHeight, imgWidth);
    myImage->detectLine(imgInBuffer, imgOutBuffer, imgWidth, imgHeight, LINE_DETECTOR_RDIA_MSK);
    myImage->writeImage();  

    std::cout << "Good Job buddy :) " << std::endl; 
    std::cout << "Image Height: " << imgHeight << std::endl; 
    std::cout << "Image Width : " << imgWidth << std::endl; 
    return 0 ;
}