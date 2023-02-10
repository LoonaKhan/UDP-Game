//
// Created by loona on 09/02/23.
//

#include "Particle.h"

namespace ptl {

    Particle::Particle(float v[2], float force[2], float decay_rate, int colour[3], float radius, float pos[2])
    : decay_rate(decay_rate), force{force[0], force[1]}, x(v[0]), y(v[1]), radius(radius)
    {
        // CircleShape properties
        this->setRadius(radius);
        this->setFillColor(sf::Color(colour[0], colour[1], colour[2]));
        this->setPosition(pos[0], pos[1]);
        this->setOrigin(radius/2, radius/2);
    }

    /*void Particle::resolveAngle(double angle) {
        this->x = cos(angle) * this->speed;
        this->y = -1 * (sin(angle) * this->speed); // positive y is down, negative y is up
    }*/

    void Particle::decay() {
        radius -=decay_rate;
        this->setRadius(radius);
    }

    void Particle::draw(sf::RenderWindow *window) {
        auto curpos = this->getPosition();

        decay(); // delete when rad<0 in our container.

        this->x -= this->force[0];
        this->y -= this->force[1];
        this->setPosition(curpos.x + this->x, curpos.y + this->y);
        window->draw(*this);
    }

    float Particle::getRadius() {
        return this->radius;
    }

    void Particle::print() {
        fmt::print(fmt::format("Particle with Velocity [{}, {}], decay rate: {}, colour: [{}, {}, {}], radius: {}, position: [{}, {}]\n",
                               this->x, this->y, this->decay_rate,
                               this->getFillColor().r, this->getFillColor().g, this->getFillColor().b,
                               this->getRadius(), this->getPosition().x, this->getPosition().y));
    }

}