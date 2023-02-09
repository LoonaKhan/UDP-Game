//
// Created by loona on 09/02/23.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "cmath"
#include "string"
#include "fmt/core.h"

namespace ptl {
    class Particle : sf::CircleShape {

    private: // members
        float speed;
        double x, y; // based off a given angle
        float decay_rate;
        float force[2];

    public: // members

    public: // methods
        Particle(float speed, float force[2], double angle, float decay_rate, int colour[3], float radius, float pos[2]);

        void print();

        void draw(sf::RenderWindow *window);


    private: // methods
        void decay();

        void resolveAngle(double angle);

    };

}
