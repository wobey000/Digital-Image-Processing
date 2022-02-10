#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

static const int _512by512_IMG_SIZE = 262144; // image size 512*512
static const int BMP_COLOR_TABLE_SIZE = 1024; 
static const int BMP_HEADER_SIZE = 54; 

class ImageProcessing
{
    public:
    // constructor 
    ImageProcessing(const char* _inImgName, const char* _outImgName, int* _height, int* _width, int* _bitDepth, unsigned char*  _header, unsigned char* _colorTable, unsigned char* _inBuf, unsigned char* _outBuf)
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

    void readImage();
    void readImage();
    void copyImage(unsigned char* _srcBuf, unsigned char* _desBuf, int bufSize); 

    virtual ~ImageProcessing(); // destructor -- virtual to avoid undefined behavior when deleting derived classes 

    protected: 

    private: 
    const char* inImgName;
    const char* outimgName; 
    int* height; 
    int* width; 
    int* bitDepth; 
    unsigned char* header; 
    unsigned char* colorTable;
    unsigned char* inBuf;  
    unsigned char* _outBuf; 
};

#endif // IMAGEPROCESSING_H