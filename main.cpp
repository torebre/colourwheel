#include "ColourWheel.h"
#include <SFML/Graphics.hpp>


void run(unsigned int height, unsigned int width, sf::Image image) {
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite;
        sprite.setTexture(texture, true);

        window.draw(sprite);

        window.display();
    }
}


int main() {
    auto colourWheel = ColourWheel();
    auto segmentPixels = colourWheel.setup(100, 100);

    int max = colourWheel.findMax(segmentPixels);
    auto pixelArray = colourWheel.createPixelArray(100, 100);

    auto mapSize = segmentPixels.size();

    sf::Image image;
    image.create(100, 100, pixelArray);

    run(100, 100, image);


//    for(int row = 0; row < mapSize; ++row) {
//        for(int column = 0; column < max; ++column) {
//            hsv()
//
//        }
//
//
//    }



//    for(int row = 0; row < 10; ++row) {
//        for(int column = 0; column < 10; ++column) {
//            std::cout << "Pixel value: " << pixelArray[row][column].x << ", " << pixelArray[row][column].y;
//        }
//    }




//    run();

    return 0;
}