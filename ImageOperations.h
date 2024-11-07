#ifndef IMAGEOPERATIONS_H
#define IMAGEOPERATIONS_H
#include "ImageData.h"

class ImageOperations {
public:

    static ImageData rotateClockwise(const ImageData& src);
    static ImageData rotateCounterClockwise(const ImageData& src);

    static void applyGaussianBlur(ImageData& img);
};

#endif