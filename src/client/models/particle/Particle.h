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
        std::pair<float, float> force;
        float radius;

    public: // members

    public: // methods
        Particle(std::pair<float, float> force, std::pair<float, float> origin,
                 sf::Color colour,
                 float radius, float decay_rate, float x, float y);

        void print();

        void draw(sf::RenderWindow *window);

        float getRadius();

        void decay();

        // getters/setters. allows particle streams to override velocities
        void setX(float new_x);

        void setY(float new_y);

        float getX();

        float getY();

    private: // methods

    };

}
