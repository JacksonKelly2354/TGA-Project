#include "TGA.h"

TGA::Header::Header(char *data) {
    idLength = data[0];
    colorMapType = data[1];
    dataTypeCode = data[2];
    colorMapOrigin = (short) ((char) data[4] + ((char) data[3] << 8));
    colorMapLength = (short) ((char) data[6] + ((char) data[5] << 8));
    colorMapDepth = data[7];
    xOrigin = (short) ((char) data[9] + ((char) data[8] << 8));
    yOrigin = (short) ((char) data[11] + ((char) data[10] << 8));
    width = (short) ((char) data[13] + ((char) data[12] << 8));
    height = (short) ((char) data[15] + ((char) data[14] << 8));
    bitsPerPixel = data[16];
    imageDescriptor = data[17];
    cout << width << " " << height << endl;
}

TGA::TGA(string filename) {
    fstream image(filename, ios_base::in | ios_base::binary);
    Header h;
    image.read(&h.idLength, 1);
    image.read(&h.colorMapType, 1);
    image.read(&h.dataTypeCode, 1);
    image.read((char*)&h.colorMapOrigin, 2);
    image.read((char*)&h.colorMapLength, 2);
    image.read(&h.colorMapDepth, 1);
    image.read((char*)&h.xOrigin, 2);
    image.read((char*)&h.yOrigin, 2);
    image.read((char*)&h.width, 2);
    image.read((char*)&h.height, 2);
    image.read(&h.bitsPerPixel, 1);
    image.read(&h.imageDescriptor, 1);
    headers.push_back(h);
    int numPixels = h.height * h.width;
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    for(int i = 0; i < numPixels; i++){
        image.read((char*)&blue, 1);
        image.read((char*)&green, 1);
        image.read((char*)&red, 1);
        Pixel newPixel = Pixel(blue, green, red);
        pixels.push_back(newPixel);
    }

}

void TGA::output(string filename, vector<Pixel> outPixels) {
    fstream image(filename, ios_base::out | ios_base::binary);
    image.write(&headers.at(0).idLength, 1);
    image.write(&headers.at(0).colorMapType, 1);
    image.write(&headers.at(0).dataTypeCode, 1);
    image.write((char*)&headers.at(0).colorMapOrigin, 2);
    image.write((char*)&headers.at(0).colorMapLength, 2);
    image.write(&headers.at(0).colorMapDepth, 1);
    image.write((char*)&headers.at(0).xOrigin, 2);
    image.write((char*)&headers.at(0).yOrigin, 2);
    image.write((char*)&headers.at(0).width, 2);
    image.write((char*)&headers.at(0).height, 2);
    image.write(&headers.at(0).bitsPerPixel, 1);
    image.write(&headers.at(0).imageDescriptor, 1);

    for(int i = 0; i < outPixels.size(); i++){
        image.write((char*)&outPixels.at(i).blue, 1);
        image.write((char*)&outPixels.at(i).green, 1);
        image.write((char*)&outPixels.at(i).red, 1);
    }
}

unsigned char TGA::multiply(unsigned char num1, unsigned char num2) {
    float temp = ((float)num1 / 255.0f) * ((float)num2 / 255.0f);
    unsigned char final = temp * 255.0f + 0.5f;
    return final;
}

void TGA::multiplyFiles(TGA layer2) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = multiply(pixels.at(i).blue, layer2.pixels.at(i).blue);
        pixels.at(i).green = multiply(pixels.at(i).green, layer2.pixels.at(i).green);
        pixels.at(i).red = multiply(pixels.at(i).red, layer2.pixels.at(i).red);
    }
}

unsigned char TGA::subtract(unsigned char num1, unsigned char num2) {
    if((float)num1 > (float)num2){
        unsigned char final = (float)num1-(float)num2;
        return final;
    } else {
        return 0;
    }

}

void TGA::subtractFiles(TGA topLayer) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = subtract(pixels.at(i).blue, topLayer.pixels.at(i).blue);
        pixels.at(i).green = subtract(pixels.at(i).green, topLayer.pixels.at(i).green);
        pixels.at(i).red = subtract(pixels.at(i).red, topLayer.pixels.at(i).red);
    }
}

unsigned char TGA::screen(unsigned char num1, unsigned char num2) {
    float temp = (1-((float)num1 / 255.0f)) * (1-((float)num2 / 255.0f));
    unsigned char final = (1-temp) * 255.0f + 0.5f;
    return final;
}

void TGA::screenFiles(TGA layer2) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = screen(pixels.at(i).blue, layer2.pixels.at(i).blue);
        pixels.at(i).green = screen(pixels.at(i).green, layer2.pixels.at(i).green);
        pixels.at(i).red = screen(pixels.at(i).red, layer2.pixels.at(i).red);
    }
}

unsigned char TGA::overlay(unsigned char num1, unsigned char num2) {
    float tempNum2 = ((float)num2 / 255.0f);
    float tempNum1 = ((float)num1 / 255.0f);
    unsigned char final;
    if (tempNum2 <= 0.5){
        final = (2 * tempNum1 * tempNum2 * 255.0f) + 0.5f;
    } else {
        final = (1-(2*(1-tempNum1)*(1-tempNum2))) * 255.0f + 0.5f;
    }
    return final;
}

void TGA::overlayFiles(TGA layer2) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = overlay(pixels.at(i).blue, layer2.pixels.at(i).blue);
        pixels.at(i).green = overlay(pixels.at(i).green, layer2.pixels.at(i).green);
        pixels.at(i).red = overlay(pixels.at(i).red, layer2.pixels.at(i).red);
    }
}

unsigned char TGA::addValue(unsigned char num1, float num2) {
    float temp = (float)(num1) + num2;
    if (temp < 255){
        if(temp < 0) {
            return 0;
        }
        unsigned char final = temp;
        return final;
    } else {
        return 255;
    }
}

void TGA::add(float blueAddValue, float greenAddValue, float redAddValue) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = addValue(pixels.at(i).blue, blueAddValue);
        pixels.at(i).green = addValue(pixels.at(i).green, greenAddValue);
        pixels.at(i).red = addValue(pixels.at(i).red, redAddValue);
    }
}

unsigned char TGA::scaleValue(unsigned char num1, float num2) {
    float temp = ((float)num1 / 255.0f);
    temp *= (num2 * 255.0f);
    unsigned char final;
    if (temp > 255){
        return 255;
    } else {
        final = temp;
        return final;
    }
}

void TGA::scale(float blueScaleValue, float greenScaleValue, float redScaleValue) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = scaleValue(pixels.at(i).blue, blueScaleValue);
        pixels.at(i).green = scaleValue(pixels.at(i).green, greenScaleValue);
        pixels.at(i).red = scaleValue(pixels.at(i).red, redScaleValue);
    }
}

void TGA::redChannel() {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = pixels.at(i).red;
        pixels.at(i).green = pixels.at(i).red;
    }
}

void TGA::greenChannel() {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = pixels.at(i).green;
        pixels.at(i).red = pixels.at(i).green;
    }
}

void TGA::blueChannel() {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).red = pixels.at(i).blue;
        pixels.at(i).green = pixels.at(i).blue;
    }
}

void TGA::combine(TGA greenFile, TGA redFile) {
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).green = greenFile.pixels.at(i).green;
        pixels.at(i).red = redFile.pixels.at(i).red;
    }
}

void TGA::flip() {
    Pixel tempPixel(0, 0, 0);
    vector<Pixel> tempPixels;
    for (int i = 0; i < pixels.size(); i++){
        tempPixel.blue = pixels.at(i).blue;
        tempPixel.green = pixels.at(i).green;
        tempPixel.red = pixels.at(i).red;
        tempPixels.push_back(tempPixel);
    }
    int counter = (pixels.size()-1);
    for (int i = 0; i < pixels.size(); i++){
        pixels.at(i).blue = tempPixels.at(counter).blue;
        pixels.at(i).green = tempPixels.at(counter).green;
        pixels.at(i).red = tempPixels.at(counter).red;
        counter -= 1;
    }
}

