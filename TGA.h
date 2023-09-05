#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class TGA {
    struct Header {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;

        Header(){

        }
        explicit Header(char *data);
    };
    // Header* header;
    vector<Header> headers;
    // attribute pixel data
    struct Pixel{
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        Pixel(unsigned char _blue, unsigned char _green, unsigned char _red) : red(_red), green(_green), blue(_blue){};
    };
    // Pixel* pixels;

public:
    vector<Pixel> pixels;
    TGA(string filename);
    unsigned char multiply(unsigned char num1, unsigned char num2);
    void multiplyFiles(TGA layer2);
    unsigned char subtract(unsigned char num1, unsigned char num2);
    void subtractFiles(TGA topLayer);
    unsigned char screen(unsigned char num1, unsigned char num2);
    void screenFiles(TGA layer2);
    unsigned char overlay(unsigned char num1, unsigned char num2);
    void overlayFiles(TGA layer2);
    unsigned char addValue(unsigned char num1, float num2);
    void add(float blueAddValue, float greenAddValue, float redAddValue);
    unsigned char scaleValue(unsigned char num1, float num2);
    void scale(float blueScaleValue, float greenScaleValue, float redScaleValue);
    void redChannel();
    void greenChannel();
    void blueChannel();
    void combine(TGA greenFile, TGA redFile);
    void flip();
    void output(string filename, vector<Pixel> outPixels);

};

