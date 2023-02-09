//
// Created by loona on 09/02/23.
//

#include "../particle/Particle.h"
#include "fmt/core.h"
#include "cmath"

void ParticleInitTest() {
    int colour[] = {3,0,0};
    float pos[] = {0,1};
    auto p = ptl::Particle(0.54, 3*M_PI / 2, 0.01, colour, 5, pos);
    p.print();
}

void DrawTest() {
    // create the particle
    int colour[] = {255,255,255};
    float pos[] = {960,540};
    auto p = ptl::Particle(10, // speed
                           4, // direction in radians
                           0.5, // decay rate
                           colour,
                           30, // radius
                           pos
                           );

    sf::RenderWindow window(
            sf::VideoMode(1920, 1080),
            "particle test",
            sf::Style::Close | sf::Style::Resize);
    sf::Clock clock;

    // loop
    while (window.isOpen()) {
        sf::Event E{};
        while (window.pollEvent(E)) {
            if (E.type == E.Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
        }
        p.draw(&window);


        window.display();
        window.clear();
        window.setFramerateLimit(60);
    }
}


int main() {
    //ParticleInitTest();
    DrawTest();
}