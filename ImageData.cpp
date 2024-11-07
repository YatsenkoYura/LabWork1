#include "ImageData.h"
#include <fstream>
#include <iostream>
ImageData::~ImageData() {
    freeMemory();
}

ImageData::ImageData() : pixels(nullptr) {}

bool ImageData::loadFromFile(const char* path) {

    std::ifstream infile(path, std::ios::binary);
    if (!infile) {
        std::cerr << "Не открыть файл: " << path << "\n";
        return false;
    }

    infile.read(reinterpret_cast<char*>(&fileHdr), sizeof(fileHdr));
    if (fileHdr.typeID != 0x4D42) {
        std::cerr << "не BMP: " << path << "\n";
        return false;
    }


    infile.read(reinterpret_cast<char*>(&infoHdr), sizeof(infoHdr));

    const int w = infoHdr.width;
    const int h = std::abs(infoHdr.height);


    const int pad = (4 - (w * 3) % 4) % 4;

    pixels = new Pixel*[h];

    for (int i = 0; i < h; ++i) {
        pixels[i] = new Pixel[w];
    }
    infile.seekg(fileHdr.offset, std::ios::beg);

    for (int i = h - 1; i >= 0; --i) {
        for (int j = 0; j < w; ++j)
        {
            infile.read(reinterpret_cast<char*>(&pixels[i][j]), 3);

            pixels[i][j].reserved = 0;}
        infile.ignore(pad);
    }

    return true;
}

bool ImageData::writeToFile(const char* path) const {
    std::ofstream outfile(path, std::ios::binary);
    if (!outfile) {
        std::cerr << "файл не создался" << path << "\n";
        return false;
    }

    outfile.write(reinterpret_cast<const char*>(&fileHdr), sizeof(fileHdr));
    outfile.write(reinterpret_cast<const char*>(&infoHdr), sizeof(infoHdr));

    const int w = infoHdr.width;
    const int h = std::abs(infoHdr.height);
    const int pad = (4 - (w * 3) % 4) % 4;

    outfile.seekp(fileHdr.offset, std::ios::beg);

    for (int i = h - 1; i >= 0; --i) {
        for (int j = 0; j < w; ++j) {
            outfile.write(reinterpret_cast<const char*>(&pixels[i][j]), 3);
        }
        constexpr char padding[3] = {0, 0, 0};
        outfile.write(padding, pad);
    }

    return true;
}

void ImageData::freeMemory() {
    if (pixels) {
        int h = std::abs(infoHdr.height);
        for (int i = 0; i < h; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }
}