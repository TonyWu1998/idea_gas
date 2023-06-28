//
// Created by tony on 3/21/21.
//

#include "histogram.h"
#include "gas_container.h"
#include "particle.h"

namespace Histogram {
  Histogram::Histogram(float lower_x, float upper_x, float lower_y, float upper_y, float lower_x1, float upper_x1,
                       float lower_y1, float upper_y1) {
    // a constructor to initialize the histogram, drawing on the board.
    lower_x_ = lower_x;
    upper_x_ = upper_x;
    lower_y_ = lower_y;
    upper_y_ = upper_y;
    lower_x1_ = lower_x1;
    upper_x1_ =  upper_x1;
    lower_y1_ = lower_y1;
    upper_y1_ = upper_y1;
  }

  void Histogram::DrawHistogram() {
    ci::gl::color(ci::Color("grey"));
    ci::Rectf rect_frame = ci::Rectf(vec2(upper_x_, upper_y_), vec2(lower_x_, lower_y_));
    ci::gl::drawSolidRect(rect_frame);
    ci::Rectf rect_graph = ci::Rectf(vec2(upper_x1_, upper_y1_), vec2(lower_x1_, lower_y1_));
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidRect(rect_graph);
    ci::gl::color(ci::Color("orange"));

    // drawing lables
    // excerpted from https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410
    ci::gl::drawStringCentered(kLableX, vec2((upper_x1_ - lower_x1_)/2 + lower_x1_, upper_y1_ + kThreshold), ci::ColorA(2,2,2,2), kXFont);
    ci::gl::pushModelMatrix();
    ci::gl::translate(lower_x1_ - kThreshold, (upper_y1_ - lower_y1_)/2 + lower_y1_);
    ci::gl::rotate(-(float) 3.1415926 / 2);
    ci::gl::drawStringCentered(kLableY, vec2(0, 0), ci::ColorA(2,2,2,2), kYFont);
    ci::gl::popModelMatrix();
  }

  void Histogram::DrawBars(const std::vector<Particle::Particle> particles,
                           int index, float mass1, float mass2, float mass3) {
    // first histogram
    float target_mass = 0;
    switch (index) {
      case 0:
        target_mass = mass1;
        break;

      case 1:
        target_mass = mass2;
        break;

      case 2:
        target_mass = mass3;
        break;

      default:
        break;
    }



    // find the max speed of this type of particles
    float offset_speed_each = 0;
    float max_speed = 0;
    for (size_t i = 0; i < particles.size(); i++) {
      if (particles[i].mass_ == target_mass) {
        float temp = std::abs(particles[i].velocity_[0]) + std::abs(particles[i].velocity_[1]);
        if (temp > max_speed)
          max_speed = temp;
      }
    }

    float rounding = max_speed / 10000;
    offset_speed_each = (max_speed + rounding) / kNumSpeed;

    float width_each = (upper_x1_ - lower_x1_) / kNumSpeed;
    std::vector<ci::Rectf> x_bars;
    std::vector<int> num_particles;


    // finding the numbers of the particles in the certain bars
    int max_num = 0;
    for (size_t i = 0; i < kNumSpeed; i++) {
      float lower = 0 + i*offset_speed_each;
      float upper = lower + offset_speed_each;

      int count = 0;
      for (size_t j = 0; j < particles.size(); j++) {
        if (particles[j].mass_ == target_mass) {

          float temp = std::abs(particles[j].velocity_[0]) + std::abs(particles[j].velocity_[1]);
          if (temp >= lower && temp < upper) {
            count++;
          }
        }
      }
      if (count > max_num)
        max_num = count;
      num_particles.push_back(count);
    }

    // drawing bars based on the found counts of the particles
    float temp = lower_x1_;
    for (size_t i = 0; i < kNumSpeed; i++) {
      float height = upper_y1_ - lower_y1_;
      float ratio = 0;
      if (max_num != 0) {
        ratio = (float) num_particles[i] / (max_num);
      }
      height = ratio * (height - kThreshold);
      ci::Rectf curr_bar = ci::Rectf(vec2(temp+width_each, upper_y1_), vec2(temp, upper_y1_ - height));
      temp += width_each;
      ci::gl::drawSolidRect(curr_bar);
    }
  }
}
