#include "ColourWheel.h"
#include <cmath>
#include <iostream>
#include <Config.hpp>
#include <Graphics.hpp>


ColourWheel::ColourWheel() {
    init();
}

ColourWheel::~ColourWheel() {
    // TODO Check if it has been initialized
    delete segmentPixelList;
}

void ColourWheel::init() {
    hsvColourLookupTable = createHsvSegmentColours();
    colourLookupTable = createSegmentColours(hsvColourLookupTable);
}

void ColourWheel::setup(int numberOfRowsInput, int numberOfColumnsInput) {
    numberOfRows = numberOfRowsInput;
    numberOfColumns = numberOfColumnsInput;

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
        }
    }

    createPixelArray(numberOfRows, numberOfColumns);
}


sf::Uint8 *ColourWheel::getPixelArray() {
    return currentPixelArray;
}

void ColourWheel::createPixelArray(int height, int width) {
    auto mapSize = segmentPixelsMap.size();
    auto segmentPixelColours = new sf::Uint8[height * width * 4];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            auto coordinate = 4 * i * width;
            segmentPixelColours[coordinate + j] = 0;
            segmentPixelColours[coordinate + j + 1] = 0;
            segmentPixelColours[coordinate + j + 2] = 0;
            segmentPixelColours[coordinate + j + 3] = 0;
        }
    }

    for (unsigned long i = 0; i < mapSize; ++i) {
        auto colour = colourLookupTable[i];

        for (auto const iterator : segmentPixelsMap[i]) {
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y] = colour.r;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 1] = colour.g;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 2] = colour.b;
            segmentPixelColours[4 * iterator.x * width + 4 * iterator.y + 3] = colour.a;
        }
    }

    currentPixelArray = segmentPixelColours;
}

sf::Color *ColourWheel::createSegmentColours(Hsv *hsvColour) {
    double hue = 0;
    auto lookupTable = new sf::Color[NUMBER_OF_SEGMENTS];

    for (int i = 0; i < NUMBER_OF_SEGMENTS; ++i) {
        hue += HUE_CHANGE;
        lookupTable[i] = hsv(hsvColour[i].h, hsvColour[i].s, hsvColour[i].v);
    }

    return lookupTable;
}

ColourWheel::Hsv *ColourWheel::createHsvSegmentColours() {
    double hue = 0;
    auto lookupTable = new ColourWheel::Hsv[NUMBER_OF_SEGMENTS];

    for (int i = 0; i < NUMBER_OF_SEGMENTS; ++i) {
        hue += HUE_CHANGE;
        lookupTable[i] = Hsv{hue, 0.5, 1.0};
    }

    return lookupTable;
}

void ColourWheel::highlightSegment(int segmentToHighlight) {
    if (currentHighlight != -1) {
        auto originalColour = hsvColourLookupTable[segmentToHighlight];
        auto colour = hsv(originalColour.h, originalColour.s, originalColour.v);

        highlightSegmentInternal(currentHighlight, &colour);
    }

    currentHighlight = segmentToHighlight;

    auto originalColour = hsvColourLookupTable[segmentToHighlight];
    auto colourToUse = hsv(originalColour.h, 1.0, originalColour.v);

    highlightSegmentInternal(segmentToHighlight, &colourToUse);

}

void ColourWheel::highlightSegmentInternal(int segmentToHighlight, sf::Color *colour) {
    auto segment = segmentPixelsMap[segmentToHighlight];


    for (auto const iterator : segment) {
        currentPixelArray[4 * iterator.x * numberOfColumns + 4 * iterator.y] = colour->r;
        currentPixelArray[4 * iterator.x * numberOfColumns + 4 * iterator.y + 1] = colour->g;
        currentPixelArray[4 * iterator.x * numberOfColumns + 4 * iterator.y + 2] = colour->b;
        currentPixelArray[4 * iterator.x * numberOfColumns + 4 * iterator.y + 3] = colour->a;
    }
}


// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
sf::Color ColourWheel::hsv(int hue, float sat, float val) {
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f) sat = 0.f;
    if (sat > 1.f) sat = 1.f;

    if (val < 0.f) val = 0.f;
    if (val > 1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val * (1.f - sat);
    float q = val * (1.f - sat * f);
    float t = val * (1.f - sat * (1 - f));

    switch (h) {
        default:
        case 0:
        case 6:
            return sf::Color(val * 255, t * 255, p * 255);
        case 1:
            return sf::Color(q * 255, val * 255, p * 255);
        case 2:
            return sf::Color(p * 255, val * 255, t * 255);
        case 3:
            return sf::Color(p * 255, q * 255, val * 255);
        case 4:
            return sf::Color(t * 255, p * 255, val * 255);
        case 5:
            return sf::Color(val * 255, p * 255, q * 255);
    }
}
