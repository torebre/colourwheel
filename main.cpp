#include "ColourWheel.h"
#include <SFML/Graphics.hpp>
#include <iostream>


#define NUMBER_OF_ROWS 100
#define NUMBER_OF_COLUMNS 100



void createImage(ColourWheel *colourWheel, sf::Image *image) {
    auto pixelArray = colourWheel->getPixelArray();
    image->create(100, 100, pixelArray);
}

void run(unsigned int height, unsigned int width, ColourWheel *colourWheel) {
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");

    int segment = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::Texture texture;
        sf::Image image;
        createImage(colourWheel, &image);

        colourWheel->highlightSegment(segment);

        std::cout << "Segment: " << segment << "\n";

        ++segment;
        if(segment == 100) {
            segment = 0;
        }

        texture.loadFromImage(image);
        sf::Sprite sprite;
        sprite.setTexture(texture, true);

        window.draw(sprite);

        window.display();
    }
}



int main() {
    auto colourWheel = ColourWheel();
    colourWheel.setup(NUMBER_OF_ROWS, NUMBER_OF_COLUMNS);

    run(100, 100, &colourWheel);

    return 0;
}