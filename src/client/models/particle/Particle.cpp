//
// Created by loona on 09/02/23.
//

#include "Particle.h"

namespace ptl {

    Particle::Particle(std::pair<float, float> force, std::pair<float, float> origin,
                       sf::Color colour,
                       float radius, float decay_rate, float x, float y)
    : decay_rate(decay_rate), force(force), x(x), y(y), radius(radius)
    {
        // CircleShape properties
        this->setRadius(radius);
        this->setFillColor(colour);
        this->setPosition(origin.first, origin.second);
        this->setOrigin(radius/2, radius/2);
    }

    void Particle::decay() {
        radius -=decay_rate;
        this->setRadius(radius);
    }

    void Particle::draw(sf::RenderWindow *window) {
        auto curpos = this->getPosition();

        decay(); // delete when rad<0 in our container.

        //acceleration
        this->x -= this->force.first;
        this->y -= this->force.second;

        // movement
        this->setPosition(curpos.x + this->x, curpos.y + this->y);
        window->draw(*this);
    }

    float Particle::getRadius() {
        return this->radius;
    }

    void Particle::setX(float new_x) {
        this->x = new_x;
    }

    void Particle::setY(float new_y) {
        this->y = new_y;
    }

    float Particle::getX() {
        return x;
    }

    float Particle::getY() {
        return y;
    }

    void Particle::print() {
        fmt::print(fmt::format("Particle with Velocity [{}, {}], decay rate: {}, colour: [{}, {}, {}], radius: {}, position: [{}, {}]\n",
                               this->x, this->y, this->decay_rate,
                               this->getFillColor().r, this->getFillColor().g, this->getFillColor().b,
                               this->getRadius(), this->getPosition().x, this->getPosition().y));
    }

}