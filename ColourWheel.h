#ifndef UNTITLED_COLOURWHEEL_H
#define UNTITLED_COLOURWHEEL_H

#include <vector>
#include <map>
#include <Graphics.hpp>

class ColourWheel {

public:

    ColourWheel();

    ~ColourWheel();


    typedef struct {
        int x;
        int y;
    } Pixel;

    typedef std::map<int, std::vector<Pixel>> PixelMap;

    void setup(int numberOfRows, int numberOfColumns);

    void createPixelArray(int height, int width);

    sf::Uint8 *getPixelArray();

    void highlightSegment(int segmentToHighlight);

    void init();


private:
    int numberOfRows;
    int numberOfColumns;

    int currentHighlight = -1;

    Pixel **segmentPixelList;

    PixelMap segmentPixelsMap;

    sf::Uint8 *currentPixelArray;

    sf::Color *colourLookupTable;

    typedef struct {
        double h;
        double s;
        double v;
    } Hsv;

    Hsv *hsvColourLookupTable;

    static const unsigned int NUMBER_OF_SEGMENTS = 100;
    static constexpr double HUE_CHANGE = 360.0 / NUMBER_OF_SEGMENTS;

    void highlightSegmentInternal(int segmentToHighlight, sf::Color *colour);

    Hsv *createHsvSegmentColours();

    static sf::Color *createSegmentColours(Hsv *hsvColour);

    static sf::Color hsv(int hue, float sat, float val);

};


#endif //UNTITLED_COLOURWHEEL_H
