//Yuriy Yatsenko 135624@student.spbu.ru
//hello world project

#include "ImageData.h"
#include "ImageOperations.h"
#include <iostream>
#include <cstring>
int main() {
    ImageData originalImage;

    if (!originalImage.loadFromFile("input.bmp")) {
        return 1;
    }

    ImageData cwImage = ImageOperations::rotateClockwise(originalImage);
    if (!cwImage.writeToFile("output1.bmp")) {
        std::cerr << "Ошибка при сохранении output1.bmp\n";
    }
    cwImage.freeMemory();

    ImageData ccwImage = ImageOperations::rotateCounterClockwise(originalImage);
    if (!ccwImage.writeToFile("output2.bmp")) {
        std::cerr << "Ошибка при сохранении output2.bmp\n";
    }
    ccwImage.freeMemory();

    ImageData blurredImage;
    blurredImage = originalImage;

    unsigned int width = blurredImage.infoHdr.width;

    unsigned int height = std::abs(blurredImage.infoHdr.height);
    blurredImage.pixels = new Pixel*[height];
    for (unsigned int i = 0; i < height; ++i) {
        blurredImage.pixels[i] = new Pixel[width];
        std::memcpy(blurredImage.pixels[i], originalImage.pixels[i], width * sizeof(Pixel));
    }

    ImageOperations::applyGaussianBlur(blurredImage);


    if (!blurredImage.writeToFile("output3.bmp")) {
        std::cerr << "Ошибка при сохранении output3.bmp\n";
    }
    blurredImage.freeMemory();
    originalImage.freeMemory();

    return 0;
}