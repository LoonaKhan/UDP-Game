//
// Created by loona on 10/02/23.
//

#pragma once
#include "Particle.h"
#include "vector"
#include "cmath"
#include "effolkronium/random.hpp"

using Random = effolkronium::random_static;
namespace ptl {

    class ParticleStream {

    private: // members
        std::vector<Particle> particles;
        std::vector<sf::Color> colours;
        float x, y;
        float radius;
        std::pair<float, float> force;
        std::pair<float, float> origin;
        float decay_rate;
        int num_particles;
        std::pair<float, float> variance_range;
        bool vary_if_zero;

    public: // members

    public: // methods
        ParticleStream(int num_particles, std::pair<float, float> force, std::pair<float, float> origin,
                       std::pair<float, float> variance_range,
                       std::vector<sf::Color> colours,
                       float radius, float decay_rate, float x = 0, float y= 0, bool vary_if_zero=true);

        void decay();

        void draw(sf::RenderWindow *window);

        void append(Particle p);

        void print();

    private: // methods

    };

} // ptl
