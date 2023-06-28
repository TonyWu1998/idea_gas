#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../src/particle.h"
#include "cinder/gl/gl.h"


using glm::vec2;
using std::string;
using std::unordered_map;
using std::vector;
using std::pair;

namespace idealgas {


struct particle {
    vec2 position;
    vec2 velocity;
    int radius;
    ci::Color color;
};


/*
class Particle {
 public:
  vec2 position;
  vec2 velocity;
  int radius_;
  string color;
};
 */
/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */

  GasContainer();

  GasContainer(int num_particles, bool random);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();


  /**
   * initialized the values for box
   * @param lower_x x lower boundary
   * @param upper_x x upper boundary
   * @param lower_y y lower boundary
   * @param upper_y y upper boundary
   */
  void SetBoxSize(float lower_x, float upper_x, float lower_y, float upper_y);

  /**
   * check if the particle is hitting the wall
   * @param p examining particale
   */
  bool CheckHitsWalls(Particle::Particle &p);
  /**
   * check if two particles are colliding with one and the other.
   * @param p1 particle 1
   * @param p2 particle 2
   */
   bool CheckTwoColliding(Particle::Particle &p1, Particle::Particle &p2);
 private:
  /**
   * This variable is just for the purposes of demonstrating how to make a shape move
   * across a screen. Please remove it once you start working on your code.
   */

  string particle_color_ = "orange";
  int num_particles_ = 50;
  float max_velocity_ = 0.3;

  const float kRadius1 = 1;
  const float kRadius2 = 3;
  const float kRadius3 = 5;

  const float kM1 = 1;
  const float kM2 = 4;
  const float kM3 = 7;

  const ci::Color kC1 = ci::Color("green");
  const ci::Color kC2 = ci::Color("blue");
  const ci::Color kC3 = ci::Color("red");

  float lower_box_x_ = 200;
  float lower_box_y_ = 150;
  float upper_box_x_ = 700;
  float upper_box_y_ = 500;

  const float kH1LowerX = 50;
  const float kH1UpperX = 300;
  const float kH1LowerY = 550;
  const float kH1UpperY = 850;

  const float kH2LowerX = 100;
  const float kH2UpperX = 280;
  const float kH2LowerY = 600;
  const float kH2UpperY = 780;


  const float kThreshold = 300;

  int center_y_ = 350;
  int center_x_ = 200;

  vector<Particle::Particle> particles_;
};

}  // namespace idealgas
