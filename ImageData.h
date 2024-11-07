#ifndef IMAGEDATA_H
#define IMAGEDATA_H

#include <cstdint>

#pragma pack(push, 1)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

struct InfoHeader {
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed;
    uint32_t importantColors;
};

struct FileHeader {
    uint16_t typeID;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};





#pragma pack(pop)
class ImageData {
public:
    InfoHeader infoHdr;
    FileHeader fileHdr;

    Pixel **pixels;

    ImageData();
    ~ImageData();

    bool loadFromFile(const char* path);
    bool writeToFile(const char* path) const;


    void freeMemory();
};

#endif