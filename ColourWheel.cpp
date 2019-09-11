#include "ColourWheel.h"
#include <cmath>
#include <iostream>
#include <Config.hpp>
#include <Graphics.hpp>

ColourWheel::~ColourWheel() {
    // TODO Check if it has been initialized
    delete segmentPixelList;
}

ColourWheel::PixelMap &ColourWheel::setup(int numberOfRows, int numberOfColumns) {
    int centerX = numberOfRows / 2;
    int centerY = numberOfColumns / 2;
    double angleSegment = 2 * M_PI / NUMBER_OF_SEGMENTS;

    for (int row = 0; row < numberOfRows; ++row) {
        for (int column = 0; column < numberOfColumns; ++column) {
            int xDiff = column - centerX;
            int yDiff = row - centerY;

            double angle = atan2(yDiff, xDiff);

            if (angle < 0) {
                angle += 2 * M_PI;
            }

            int segment = angle / angleSegment;
            auto pixelIterator = segmentPixelsMap.find(segment);

            if (pixelIterator == segmentPixelsMap.end()) {
                std::vector<Pixel> pixelVector = std::vector<Pixel>();
                pixelVector.push_back(Pixel{row, column});
                segmentPixelsMap[segment] = pixelVector;
            } else {
                pixelIterator->second.push_back(Pixel{row, column});
            }

//            std::cout << angle;
        }

    }

    return segmentPixelsMap;
}


sf::Uint8 *ColourWheel::createPixelArray(int height, int width) {
    auto mapSize = segmentPixelsMap.size();
    auto segmentPixelColours = new sf::Uint8[height * width * 4];

    for(int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j) {
            segmentPixelColours[4 * i * width + j] = 0;
            segmentPixelColours[4 * i * width + j + 1] = 0;
            segmentPixelColours[4 * i * width + j + 2] = 0;
            segmentPixelColours[4 * i * width + j + 3] = 0;
        }
    }

    double hue = 0;
    for (unsigned long i = 0; i < mapSize; ++i) {

        hue += HUE_CHANGE;

        for (auto const iterator : segmentPixelsMap[i]) {
            auto colour = hsv(hue, 1.0, 1.0);

            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y] = colour.r;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 1] = colour.g;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 2] = colour.b;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 3] = colour.a;
        }
    }

    return segmentPixelColours;
}


int ColourWheel::findMax(std::map<int, std::vector<Pixel>> &mapToFindMaxFrom) {
    unsigned long max = 0;

    for (auto const iterator : mapToFindMaxFrom) {
        if (max < iterator.second.size()) {
            max = iterator.second.size();
        }
    }

    return max;
}
