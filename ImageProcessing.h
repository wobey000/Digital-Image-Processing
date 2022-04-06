#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

static const int _512by512_IMG_SIZE = 262144; // image size 512*512
static const int BMP_COLOR_TABLE_SIZE = 1024; 
static const int BMP_HEADER_SIZE = 54; 
static const int MAX_COLOR = 255; 
static const int MIN_COLOR = 0;
static const int WHITE = MAX_COLOR; 
static const int BLACK = MIN_COLOR; 
static const int NO_OF_GRAYLEVELS = 255;

class ImageProcessing
{
    public:
    // constructor 
    ImageProcessing(const char* _inImgName, const char* _outImgName, int* _height, int* _width, int* _bitDepth, unsigned char*  _header, unsigned char* _colorTable, unsigned char* _inBuf, unsigned char* outBuf);
    virtual ~ImageProcessing(); // destructor -- virtual to avoid undefined behavior when deleting derived classes
    
    void readImage();
    void writeImage();
    void copyImage(unsigned char* _srcBuf, unsigned char* _desBuf, int bufSize); 
    void BrightnessUp(unsigned char* _inputImgData, unsigned char* _outImgData, int imgSize, int brightness);
    void BrightnessDown(unsigned char* _inputImgData, unsigned char* _outImgData, int imgSize, int brightness);
    void ComputeHistogram(unsigned char* _imgData, int imgRows, int imgCols, float hist[]);
    void ComputeHistogram2(unsigned char* _imgData, int imgRows, int imgCols, float hist[], const char* histFile );
    void equalizeHistogram(unsigned char* _inputImgData, unsigned char* _outputImgData, int imgRows, int imgCols);



     

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