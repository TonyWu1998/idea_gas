//
// Created by tony on 3/20/21.
//

#include "particle.h"
#include <string>

using std::string;

namespace Particle {
  using glm::vec2;

  Particle::Particle(vec2 start_position, vec2 velocity, float radius,
                     cinder::Color color, float mass) {
      position_ = start_position;
      velocity_ = velocity;
      radius_ = radius;
      color_ = color;
      mass_ = mass;
  }
}