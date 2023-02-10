//
// Created by loona on 09/02/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "cmath"
#include "string"
#include "fmt/core.h"

namespace ptl {
    class Particle : public sf::CircleShape {

    private: // members
        double x, y; // x/y velocities
        float decay_rate;
        float force[2];
        float radius;

    public: // members

    public: // methods
        Particle(float v[2], float force[2], float decay_rate, int colour[3], float radius, float pos[2]);

        void print();

        void draw(sf::RenderWindow *window);

        float getRadius();


    private: // methods
        void decay();

        void resolveAngle(double angle);

    };

}
