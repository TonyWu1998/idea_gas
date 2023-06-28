//
// Created by tony on 3/20/21.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include "cinder/gl/gl.h"
#include <string>

using std::string;
using glm::vec2;

namespace Particle {
    class Particle {
     public:
      vec2 position_;
      vec2 velocity_;
      float radius_;
      ci::Color color_;
      float mass_;
      Particle(vec2 start_position, vec2 velocity, float radius,
               cinder::Color color, float mass);
    };
}


#endif  // IDEAL_GAS_PARTICLE_H
