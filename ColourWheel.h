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

    PixelMap &setup(int numberOfRows, int numberOfColumns);

    sf::Uint8 *createPixelArray(int height, int width);

    static int findMax(PixelMap &pixelMap);

    void init();


private:

    Pixel **segmentPixelList;

    PixelMap segmentPixelsMap;


    sf::Color *colourLookupTable;

    const Pixel noValuePixel = {-1, -1};

    typedef int32_t Fixed;

    static const unsigned int NUMBER_OF_SEGMENTS = 100;
    static constexpr double HUE_CHANGE = 360.0 / NUMBER_OF_SEGMENTS;

    static sf::Color *createSegmentColours();

    static sf::Color hsv(int hue, float sat, float val);


//
//// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f
//    static sf::Color hsv(int hue, float sat, float val)
//    {
//        hue %= 360;
//        while(hue<0) hue += 360;
//
//        if(sat<0.f) sat = 0.f;
//        if(sat>1.f) sat = 1.f;
//
//        if(val<0.f) val = 0.f;
//        if(val>1.f) val = 1.f;
//
//        int h = hue/60;
//        float f = float(hue)/60-h;
//        float p = val*(1.f-sat);
//        float q = val*(1.f-sat*f);
//        float t = val*(1.f-sat*(1-f));
//
//        switch(h)
//        {
//            default:
//            case 0:
//            case 6: return sf::Color(val*255, t*255, p*255);
//            case 1: return sf::Color(q*255, val*255, p*255);
//            case 2: return sf::Color(p*255, val*255, t*255);
//            case 3: return sf::Color(p*255, q*255, val*255);
//            case 4: return sf::Color(t*255, p*255, val*255);
//            case 5: return sf::Color(val*255, p*255, q*255);
//        }
//    }


};


#endif //UNTITLED_COLOURWHEEL_H
