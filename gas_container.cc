#include "gas_container.h"
#include <stdlib.h>
#include "particle.h"
#include "histogram.h"
#include <string>

namespace idealgas {
using glm::vec2;


GasContainer::GasContainer() {

    vec2 ejection_point_1 = vec2(center_x_ + kRadius1, center_y_);
    vec2 ejection_point_2 = vec2(upper_box_x_ - kRadius2, center_y_);
    vec2 ejection_point_3 = vec2((upper_box_x_ - lower_box_x_) / 2 + lower_box_x_, lower_box_y_ + kRadius3);
    float threshold = max_velocity_ / 20;

    for (size_t i = 0; i < num_particles_; i++) {
      Particle::Particle p(ejection_point_1, vec2(i * threshold,max_velocity_ - (i * threshold)),
                           kRadius1, kC1, kM1);
      particles_.push_back(p);
    }

    for (size_t i = 0; i < num_particles_; i++) {
      Particle::Particle p(ejection_point_2, vec2(i * threshold,max_velocity_ - (i * threshold)),
                           kRadius2, kC2, kM2);
      particles_.push_back(p);
    }

    for (size_t i = 0; i < num_particles_; i++) {
      Particle::Particle p(ejection_point_3, vec2(i * threshold,max_velocity_ - (i * threshold)),
                           kRadius3, kC3, kM3);
      particles_.push_back(p);
    }

}



void GasContainer::SetBoxSize(float lower_x, float upper_x, float lower_y, float upper_y) {
  lower_box_x_ = lower_x;
  lower_box_y_ = lower_y;
  upper_box_x_ = upper_x;
  upper_box_y_ = upper_y;
}

GasContainer::GasContainer(int num_particles, bool random) {
    //AddParticlesIntoContainers(num_particles);
}

void GasContainer::Display() const {
    // This function has a lot of magic numbers; be sure to design your code in a way that avoids this.

    ci::gl::drawStrokedRect(ci::Rectf(vec2(upper_box_x_, upper_box_y_), vec2(lower_box_x_, lower_box_y_)));     // the coordinates of the rectangle box, top left(200, 150), bottom right(700, 550)

    for (size_t i = 0; i < particles_.size(); i++) {
      //string c = "orange";
      ci::gl::color(particles_[i].color_);
      ci::gl::drawSolidCircle(particles_[i].position_, particles_[i].radius_);
    }


    for (size_t i = 0; i < 3; i++) {
      Histogram::Histogram h1 = Histogram::Histogram(kH1LowerX + (i*kThreshold), kH1UpperX + (i*kThreshold), kH1LowerY, kH1UpperY,
                                                     kH2LowerX + (i*kThreshold), kH2UpperX + (i*kThreshold), kH2LowerY, kH2UpperY);
      h1.DrawHistogram();
      h1.DrawBars(particles_, i, kM1, kM2, kM3);
    }
}

bool GasContainer::CheckHitsWalls(Particle::Particle &p) {
  float curr_x = p.position_[0];
  float curr_y = p.position_[1];
  //float v_x = p.velocity_[0];
  //float v_y = p.velocity_[1];
  int particle_radius = p.radius_;


  if (lower_box_x_ > curr_x - particle_radius || upper_box_x_ <  curr_x + particle_radius) {
    p.velocity_[0] = 0 - p.velocity_[0];
    return true;
  }

  if (lower_box_y_ > curr_y - particle_radius || upper_box_y_ <  (curr_y + particle_radius)) {
    p.velocity_[1] = 0 - p.velocity_[1];
    return true;
  }


  /*
  if ((lower_box_x_ < curr_x - particle_radius) && (upper_box_x_ >  curr_x + particle_radius) &&
      (lower_box_y_ < curr_y - particle_radius) && (upper_box_y_ >  curr_y + particle_radius)) {
    return true;
  } else if ((lower_box_x_ >= curr_x - particle_radius) || (upper_box_x_ <=  curr_x + particle_radius)) {
    p.velocity_[0] = 0 - p.velocity_[0];
    return false;
  } else if ((lower_box_y_ >= curr_y - particle_radius) || (upper_box_y_ <= curr_y + particle_radius)) {
    p.velocity_[1] = 0 - p.velocity_[1];
    return false;
  }
   */

  return false;

}

bool GasContainer::CheckTwoColliding(Particle::Particle &p1, Particle::Particle &p2) {
  vec2 x1 = p1.position_;
  vec2 x2 = p2.position_;

  float m1 = p1.mass_;
  float m2 = p2.mass_;

  vec2 v1 = p1.velocity_;
  vec2 v2 = p2.velocity_;


  vec2 v1_prime = v1 - ((2*m2) / (m1 + m2)) * ((glm::dot((v1 - v2), (x1 - x2))) / (glm::length2(x1-x2))) * (x1 - x2);
  vec2 v2_prime = v2 - ((2*m1) / (m1 + m2)) * ((glm::dot((v2 - v1), (x2 - x1))) / (glm::length2(x2-x1))) * (x2 - x1);

  float dist_two = glm::length(x1-x2);
  float dir = glm::dot((v1- v2), (x1 - x2));
  if (dir < 0 && dist_two < (p1.radius_ + p2.radius_)) {
    p1.velocity_ = v1_prime;
    p2.velocity_ = v2_prime;
    return true;
  }

  return false;
}

void GasContainer::AdvanceOneFrame() {

  for (size_t i = 0; i < particles_.size(); i++) {
    if (!CheckHitsWalls(particles_[i])) {
      for(size_t j = i + 1; j < particles_.size(); j++) {
        if (CheckTwoColliding(particles_[i], particles_[j]))
          break;
      }
    }
    particles_[i].position_ += particles_[i].velocity_;
    particles_[i].position_ += particles_[i].velocity_;
  }
}

}  // namespace idealgas
