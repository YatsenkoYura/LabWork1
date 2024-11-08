//Yuriy Yatsenko 135624@student.spbu.ru
//hello world project


#include "ImageOperations.h"
#include <cmath>
#include <cstring>

ImageData ImageOperations::rotateClockwise(const ImageData& src) {
    ImageData dst;

    dst.fileHdr = src.fileHdr;

    const unsigned int origWidth = src.infoHdr.width;
    const unsigned int origHeight = std::abs(src.infoHdr.height);

    dst.infoHdr = src.infoHdr;



    dst.infoHdr.width = origHeight;
    dst.infoHdr.height = src.infoHdr.height < 0 ? -static_cast<int>(origWidth) : static_cast<int>(origWidth);

    dst.pixels = new Pixel*[origWidth];
    for (unsigned int i = 0; i < origWidth; ++i) {
        dst.pixels[i] = new Pixel[origHeight];
    }
    for (unsigned int i = 0; i < origHeight; ++i) {
        for (unsigned int j = 0; j < origWidth; ++j) {
            dst.pixels[j][origHeight - 1 - i] = src.pixels[i][j];
        }
    }

    const int newWidth = dst.infoHdr.width;



    int newHeight = std::abs(dst.infoHdr.height);
    const int padding = (4 - (newWidth * 3) % 4) % 4;


    dst.infoHdr.imageSize = (newWidth * 3 + padding) * newHeight;

    dst.fileHdr.size = dst.fileHdr.offset + dst.infoHdr.imageSize;
    return dst;
}

ImageData ImageOperations::rotateCounterClockwise(const ImageData& src) {
    ImageData dst;
    dst.fileHdr = src.fileHdr;
    dst.infoHdr = src.infoHdr;

    unsigned int origWidth = src.infoHdr.width;
    unsigned int origHeight = std::abs(src.infoHdr.height);

    dst.infoHdr.width = origHeight;
    dst.infoHdr.height = src.infoHdr.height < 0 ? -static_cast<int>(origWidth) : static_cast<int>(origWidth);

    dst.pixels = new Pixel*[origWidth];
    for (unsigned int i = 0; i < origWidth; ++i) {
        dst.pixels[i] = new Pixel[origHeight];
    }

    for (unsigned int i = 0; i < origHeight; ++i) {
        for (unsigned int j = 0; j < origWidth; ++j) {
            dst.pixels[origWidth - 1 - j][i] = src.pixels[i][j];
        }
    }

    const int newWidth = dst.infoHdr.width;
    int newHeight = std::abs(dst.infoHdr.height);
    const int padding = (4 - (newWidth * 3) % 4) % 4;
    dst.infoHdr.imageSize = (newWidth * 3 + padding) * newHeight;
    dst.fileHdr.size = dst.fileHdr.offset + dst.infoHdr.imageSize;

    return dst;
}

void ImageOperations::applyGaussianBlur(ImageData& img) {
    constexpr int K_SIZE = 3;
    constexpr float gaussianKernel[K_SIZE][K_SIZE] = {
        {1/16.0f, 2/16.0f, 1/16.0f},
        {2/16.0f, 4/16.0f, 2/16.0f},
        {1/16.0f, 2/16.0f, 1/16.0f}
    };

    unsigned int w = img.infoHdr.width;
    unsigned int h = std::abs(img.infoHdr.height);

    Pixel **copyPixels = new Pixel*[h];
    for (unsigned int i = 0; i < h; ++i) {
        copyPixels[i] = new Pixel[w];
        std::memcpy(copyPixels[i], img.pixels[i], w * sizeof(Pixel));
    }

    for (unsigned int y = 1; y < h - 1; ++y) {
        for (unsigned int x = 1; x < w - 1; ++x) {
            float r = 0.0f, g = 0.0f, b = 0.0f;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    Pixel &p = copyPixels[y + ky][x + kx];
                    r += p.red * gaussianKernel[ky + 1][kx + 1];
                    g += p.green * gaussianKernel[ky + 1][kx + 1];
                    b += p.blue * gaussianKernel[ky + 1][kx + 1];
                }
            }
            img.pixels[y][x].red = static_cast<uint8_t>(std::round(r));
            img.pixels[y][x].green = static_cast<uint8_t>(std::round(g));
            img.pixels[y][x].blue = static_cast<uint8_t>(std::round(b));
        }
    }
    for (unsigned int i = 0; i < h; ++i) {
        delete[] copyPixels[i];
    }
    delete[] copyPixels;
}