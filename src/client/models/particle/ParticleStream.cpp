//
// Created by loona on 10/02/23.
//

#include "ParticleStream.h"

namespace ptl {
    ParticleStream::ParticleStream(int num_particles,
                                   std::pair<float, float> force, std::pair<float, float> origin,
                                   std::pair<float, float> variance_range,
                                   std::vector<sf::Color> colours,
                                   float radius, float decay_rate, float x, float y,
                                   bool vary_if_zero)
                                   : colours(colours),
                                   x(x), y(y), radius(radius), decay_rate(decay_rate),
                                   force(force), origin(origin),
                                   num_particles(num_particles), variance_range(variance_range),
                                   vary_if_zero(vary_if_zero){
        // appends all initial particles to the particles vector
        for (int i = 0; i < num_particles; i++) {
            // if x and/or y are not given, randomly generate them
            float px = x, py = y;
            if (px == 0 and vary_if_zero)
                px = Random::get(this->variance_range.first, this->variance_range.second);
            if (py==0 and vary_if_zero)
                py = Random::get(this->variance_range.first, this->variance_range.second);

            auto c = Random::get(this->colours);

            auto p = Particle(force, origin, *c, radius, decay_rate, px, py);
            this->particles.emplace_back(p);

        }
    }

    void ParticleStream::decay() { // decays all particles in the vector
        auto i = this->particles.begin();
        while (i != particles.end()) {
            i->decay();
            if (i->getRadius() <= 0) // if the particle is too small, delete it
                particles.erase(i);
            else i++;
        }
    }

    void ParticleStream::draw(sf::RenderWindow *window) { // draws all particles
        for (auto& p : this->particles)
            p.draw(window);
    }

    void ParticleStream::append(ptl::Particle p) { // adds a particle to the vector
        if (p.getX()== 0 and vary_if_zero)
            p.setX(Random::get(variance_range.first, variance_range.second));
        if (p.getY() == 0 and vary_if_zero)
            p.setY(Random::get(variance_range.first, variance_range.second));

        this->particles.emplace_back(p);
    }

    void ParticleStream::print() { // prints debug info.
        fmt::print("Particle stream with {} particles"
                   ", X {}, Y {}, varies {}, variance range [{}, {}], "
                   "radius {}, origin [{}, {}], force [{}, {}], "
                   "decay_rate {} \n",
                   num_particles, x, y, vary_if_zero, variance_range.first,variance_range.second,
                   radius, origin.first, origin.second, force.first, force.second, decay_rate);
    }

} // ptl