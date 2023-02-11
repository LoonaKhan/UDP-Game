//
// Created by loona on 09/02/23.
//

#include "../particle/Particle.h"
#include "../particle/ParticleStream.h"
#include "fmt/core.h"
#include "cmath"
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

void ParticleInitTest() {
    sf::Color colour = sf::Color(3, 0, 0);
    std::pair<float, float> origin = {0,1};
    std::pair<float, float> force = {0,0.5};
    float x = 1, y = 5;
    float radius = 12;
    float decay_rate = 0.1;
    auto p = ptl::Particle(force, origin, colour, radius, decay_rate, x, y);
    p.print();
}

void DrawTest() {

    std::vector<ptl::Particle> particles;
    sf::Color colour;
    std::pair<float, float> origin = {960, 1080};
    std::pair<float, float> force;
    float radius = 12;
    float decay_rate = 0.1;
    float x=0, y=0;

    for (int i =0; i<10; i++){
        colour = sf::Color(Random::get(0,255), Random::get(0,255), Random::get(0,255));
        force.first = 0;
        force.second = -0.2;
        x = float(Random::get(-1.0, 1.0));
        y = -10;//float(Random::get(-5.0,5.0));
        particles.emplace_back(ptl::Particle(force, origin, colour, radius, decay_rate, x, y));
    }
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


        auto i = particles.begin();
        while (i!= particles.end()) {
            if (i->getRadius() <=0)
                particles.erase(i);
            else i++;
        }
        for (auto& p : particles) {
            p.draw(&window);
        }

        window.display();
        window.clear();
        window.setFramerateLimit(60);
    }
}

void ParticleStreamInitTest() {
    std::pair<float, float> force= {0,0.2};
    std::pair<float, float> origin = {960, 1080};
    std::pair<float, float> variance_range = {-5.0, 5.0};
    std::vector<sf::Color> colours = {
            sf::Color::White,
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Green
    };
    float radius = 12;
    float decay_rate = 0.1;
    float x=0, y=-10;
    bool vary_if_zero = true;
    auto ps = ptl::ParticleStream(50, force, origin, variance_range, colours, radius, decay_rate, x, y, vary_if_zero);

    ps.print();

}

void ParticleStreamTest() {
    std::pair<float, float> force= {0,0.2};
    std::pair<float, float> origin = {960, 1080};
    std::pair<float, float> variance_range = {-5.0, 5.0};
    std::vector<sf::Color> colours = {
            sf::Color::White,
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color::Green
    };
    float radius = 12;
    float decay_rate = 0.1;
    float x=0, y=-10;
    bool vary_if_zero = true;

    auto ps = ptl::ParticleStream(50, force, origin, variance_range, colours, radius, decay_rate, x, y, vary_if_zero);

    sf::RenderWindow window(
            sf::VideoMode(1920, 1080),
            "particle stream test",
            sf::Style::Close | sf::Style::Resize);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event E{};
        while (window.pollEvent(E)) {
            if (E.type == E.Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                window.close();
            }
        }

        ps.decay();
        ps.draw(&window);

        // append particle
        auto p = ptl::Particle(force, origin, *Random::get(colours), radius, decay_rate, x, y);
        ps.append(p);

        window.display();
        window.clear();
        window.setFramerateLimit(60);
    }
}

int main() {
    //ParticleInitTest();
    //DrawTest();
    ParticleStreamTest();
    //ParticleStreamInitTest();
}