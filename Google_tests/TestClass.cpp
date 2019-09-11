#include "gtest/gtest.h"
#include "../ColourWheel.cpp"


TEST(ColourWheelTest, OutputGenerated) {
    auto colourWheel = ColourWheel();

    auto segmentPixels = colourWheel.setup(10, 10);

    auto pixelArray = colourWheel.createPixelArray(10, 10);

//    for(int row = 0; row < 10; ++row) {
//        for(int column = 0; column < 10; ++column) {
//            std::cout << "Pixel value: " << pixelArray[row][column].x << ", " << pixelArray[row][column].y;
//        }
//    }






}