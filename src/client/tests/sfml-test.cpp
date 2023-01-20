//
// Created by loona on 19/01/23.
//

#include <SFML/Graphics.hpp>
#include "../models/block/Block.h"
#include "../models/chunk/Chunk.h"
#include "../globvars/globvars.h"

int main() {
    int coords[] = {5,5};

    auto c = chunk::Chunk(coords);

    auto window = sf::RenderWindow(sf::VideoMode(1920,1080),
                                   "CLIENT",
                                   sf::Style::Close | sf::Style::Resize);

    while (window.isOpen()) {
        sf::Event evnt{};

        while(window.pollEvent(evnt)) {
            if (evnt.type == evnt.Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        for (auto& b : c.getBlocks().blocks) {
                b.render(&window, c.getCoords());
            }



        window.display(); //move the back buffer to the front buffer
    }
}