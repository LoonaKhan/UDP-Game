//
// Created by loona on 09/02/23.
//

#include "../particle/Particle.h"
#include "fmt/core.h"
#include "cmath"
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

void ParticleInitTest() {
    int colour[] = {3,0,0};
    float pos[] = {0,1};
    float force[] = {0,0.5};
    float v[] = {1,5};
    auto p = ptl::Particle(v, force, 0.01, colour, 5, pos);
    p.print();
}

void DrawTest() {

    std::vector<ptl::Particle> particles;
    int colour[3] = {};
    float pos[2] = {960, 1080};
    float force[2] = {};
    float v[2] = {};

    /*for (int i =0; i<50; i++){// create the particles
        colour[0] = Random::get(0, 255); colour[1] =  Random::get(0, 255); colour[2] =  Random::get(0, 255);
        force[0] =  0; force[1] =-0.1;
        v[0] = float(Random::get(-1.0, 1.0)); v[1]= -15;
        particles.push_back(ptl::Particle(v, // velocity
                                     force,
                                     0.1, // decay rate
                                     colour,
                                     15, // radius
                                     pos

        ));
    }*/

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

        colour[0] = Random::get(0, 255);
        colour[1] =  255;
        colour[2] =  Random::get(0, 255);
        force[0] =  0;
        force[1] =-0.2;
        v[0] = float(Random::get(-2.0, 2.0));
        v[1]= -15;
        particles.emplace_back(ptl::Particle(v, force, 0.1,colour, 12, pos));

        for (auto i=particles.begin(); i!= particles.end();i++) {
            if (i->getRadius() <=0)
                particles.erase(i);
        }
        for (auto& p : particles) {
            p.draw(&window);
        }


        window.display();
        window.clear();
        window.setFramerateLimit(60);
        //std::cout << particles.size() << std::endl;
    }
}


int main() {
    //ParticleInitTest();
    DrawTest();
}