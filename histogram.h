//
// Created by tony on 3/21/21.
//

#ifndef IDEAL_GAS_HISTOGRAM_H
#define IDEAL_GAS_HISTOGRAM_H
#include <string>
#include <vector>
#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;
using std::string;

namespace Histogram {

  class Histogram {
   public:
    Histogram(float lower_x, float upper_x, float lower_y, float upper_y, float lower_x1, float upper_x1,
              float lower_y1, float upper_y1);

    /**
     * draw the histogram frame
     */
    void DrawHistogram();

    /**
     * draw the bars in the histogram
     */
    void DrawBars(const std::vector<Particle::Particle> vector, int index,
                  float mass1, float mass2, float mass3);

   private:
    float lower_x_;
    float upper_x_;
    float lower_y_;
    float upper_y_;
    float lower_x1_;
    float upper_x1_;
    float lower_y1_;
    float upper_y1_;

    const float kThreshold = 10;
    const string kLableX = "Speeds";
    const string kLableY = "Frequencies";
    const ci::Font kXFont = ci::Font("Arial", 10);
    const ci::Font kYFont = ci::Font("Arial", 10);

    const float kNumSpeed = 20;



  };
}


#endif  // IDEAL_GAS_HISTOGRAM_H
