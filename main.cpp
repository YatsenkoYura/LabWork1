//Yuriy Yatsenko 135624@student.spbu.ru
//hello world project

#include "ImageData.h"
#include "ImageOperations.h"
#include <iostream>
#include <cstring>
#include <thread>
int main() {
    ImageData originalImage;
    if (!originalImage.loadFromFile("input.bmp")) {
        return 1;
    }

    std::thread t1([&originalImage]() {
        ImageData cw = ImageOperations::rotateClockwise(originalImage);
        if (!cw.writeToFile("output1.bmp")) {
            std::cerr << "Ошибка при сохранении output1.bmp\n";
        }
        cw.freeMemory();
    });

    std::thread t2([&originalImage]() {
        ImageData ccw = ImageOperations::rotateCounterClockwise(originalImage);
        if (!ccw.writeToFile("output2.bmp")) {
            std::cerr << "Ошибка при сохранении output2.bmp\n";
        }
        ccw.freeMemory();
    });

    std::thread t3([&originalImage]() {
        ImageData blurred;
        blurred = originalImage;

        unsigned int w = originalImage.infoHdr.width;
        unsigned int h = std::abs(originalImage.infoHdr.height);
        blurred.pixels = new Pixel*[h];
        for (unsigned int i = 0; i < h; ++i) {
            blurred.pixels[i] = new Pixel[w];
            std::memcpy(blurred.pixels[i], originalImage.pixels[i], w * sizeof(Pixel));
        }

        ImageOperations::applyGaussianBlur(blurred);

        if (!blurred.writeToFile("output3.bmp")) {
            std::cerr << "Ошибка при сохранении output3.bmp\n";
        }
        blurred.freeMemory();
    });

    t1.join();
    t2.join();
    t3.join();

    originalImage.freeMemory();
    return 0;
}