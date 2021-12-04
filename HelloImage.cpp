#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "Hello World Image Processing \n" << std::endl; 

    FILE *streamIn = fopen("images/cameraman.bmp", "rb"); // input: read and store into stream 
    FILE *fileOut = fopen("images/cameraman_my_copy_one.bmp", "wb"); // output: write to file 

    // error checking 
    if(streamIn == (FILE*)0)
    {
        std::cout << "Unable to open file" << std::endl; 
    }

    // store bitmap image properties 
    unsigned char header[54]; 
    unsigned char colorTable[1024]; 

    // extract image header 
    for(int i = 0; i < 54; i++)
    {
        header[i] = getc(streamIn); 
    }

    int image_width = *(int *)&header[18]; // image width is at offset 18 in header
    int image_height = *(int *)&header[22]; // image height is at offset 22 in header 
    int image_bit_depth = *(int *)&header[28]; // image bitDepth or bits/pixel is at offset 28 in header 

    // check if we have a color table - less than 8 means we have a color table  
    if(image_bit_depth <= 8)
    {
        fread(colorTable, sizeof(unsigned char), 1024, streamIn); // if exist then read into color table array  
    }

    // write image header to output file after done extracting properties 
    fwrite(header, sizeof(unsigned char), 54, fileOut); 

    // buffer for storing image data 
    unsigned char my_buffer[image_height * image_width]; 
    fread(my_buffer, sizeof(unsigned char), (image_height * image_width), streamIn); 

    // read pixel data 
    fread(my_buffer, sizeof(unsigned char), (image_height*image_width), streamIn); 

    if(image_bit_depth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), 1024, fileOut); 
    }

    fwrite(my_buffer, sizeof(unsigned char), (image_height*image_width), fileOut); 
    fclose(fileOut);
    fclose(streamIn); 

    std::cout << "Success ! Done fam" << std::endl; 
    std::cout << " Image Width: " << image_width << std::endl; 
    std::cout << "Image Height: " << image_height << std::endl; 

    return 0;
}
