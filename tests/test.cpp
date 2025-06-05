#include "gtest/gtest.h"
#include "../include/ImageData.h"
#include "../include/ImageOperations.h"
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;

TEST(SimpleImageOps, JustRunAllOps) {
    ImageData orig;
    bool loaded = orig.loadFromFile("test_file/input.bmp");
    ASSERT_TRUE(loaded) << "Не удалось загрузить test_file/input.bmp";

    {
    ImageData cw = ImageOperations::rotateClockwise(orig);
    EXPECT_TRUE(cw.writeToFile("test_file/out_cw.bmp"))
    << "Не удалось сохранить out_cw.bmp";
    cw.freeMemory();
    }

    {
    ImageData ccw = ImageOperations::rotateCounterClockwise(orig);
    EXPECT_TRUE(ccw.writeToFile("test_file/out_ccw.bmp"))
    << "Не удалось сохранить out_ccw.bmp";
    ccw.freeMemory();
    }

    {
    ImageData blur = orig;
    unsigned H = std::abs(orig.infoHdr.height);
    unsigned W = orig.infoHdr.width;
    blur.pixels = new Pixel*[H];
    for (unsigned i = 0; i < H; ++i) {
    blur.pixels[i] = new Pixel[W];
    std::memcpy(blur.pixels[i], orig.pixels[i], W * sizeof(Pixel));
    }

    EXPECT_TRUE(blur.writeToFile("test_file/out_blur.bmp"))
    << "Не удалось сохранить out_blur.bmp";
    blur.freeMemory();
    }

    orig.freeMemory();

    EXPECT_TRUE(fs::exists("test_file/out_cw.bmp"));
    EXPECT_TRUE(fs::exists("test_file/out_ccw.bmp"));
    EXPECT_TRUE(fs::exists("test_file/out_blur.bmp"));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}