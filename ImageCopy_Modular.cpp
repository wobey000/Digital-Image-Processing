#include <iostream>

const int BMP_HEADER_SIZE = 54; 
const int BMP_COLOR_TABLE_SIZE = 1024; 
const int CUSTOM_IMG_SIZE = 1024*1024; 

// Function Prototypes 
void imageReader(const char* imgName, int* _height, int* _width, int* _bitDepth, unsigned char* _header, unsigned char* _colorTable, unsigned char* _buff);
void imageWriter(const char* imgName, unsigned char* header, unsigned char* colorTable, unsigned char* buf, int bitDepth);  


int main(int argc, char const *argv[])
{
    std::cout << "Hello World Image Processing " << std::endl;
    std::cout << "Function Tests" << std::endl;   

    int imgWidth;
    int imgHeight;
    int imgBitDepth;
    unsigned char imgHeader[BMP_HEADER_SIZE]; 
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgBuffer[CUSTOM_IMG_SIZE]; 

    const char imgName[] = "images/man.bmp"; 
    const char newImgName[] = "images/man_copy.bmp"; 

    imageReader(imgName, &imgHeight, &imgWidth, &imgBitDepth, imgHeader, imgColorTable, &imgBuffer[0]);
    imageWriter(newImgName, imgHeader, imgColorTable, imgBuffer, imgBitDepth); 

    std::cout << "Successfil :D " << std::endl;  

    return 0;
}

void imageReader(const char* imgName, int* _height, int* _width, int* _bitDepth, unsigned char* _header, unsigned char* _colorTable, unsigned char* _buff)
{
    FILE *streamIn;
    streamIn = fopen(imgName, "rb");

    // file check like before 
    if(streamIn == (FILE *)0)
    {
        std::cout << "unable to open image" << std::endl; 
    }

    for( int i = 0; i < BMP_HEADER_SIZE; i++)
    {
        _header[i] = getc(streamIn); 
    }

    *_width = *(int *)&_header[18]; 
    *_height = *(int *)&_header[22]; 
    *_bitDepth = *(int *)&_header[28]; 

    // Color table check 
    if(*_bitDepth <= 8)
    {
        fread(_colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }

    // Read Pixel Info
    fread(_buff, sizeof(unsigned char), CUSTOM_IMG_SIZE, streamIn);

    //Done so close file 
    fclose(streamIn); 
}

void imageWriter(const char* imgName, unsigned char* header, unsigned char* colorTable, unsigned char* buf, int bitDepth)
{
    FILE *fileOut = fopen(imgName, "wb"); 
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fileOut); 

    if(bitDepth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fileOut); 
    }

    fwrite(buf, sizeof(unsigned char), CUSTOM_IMG_SIZE, fileOut); 

    //Done so close file 
    fclose(fileOut); 
}
