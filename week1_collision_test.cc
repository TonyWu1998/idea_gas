#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Hitting Walls Tests") {
  SECTION("Hit left side wall") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(200, 350), vec2(-1, 0)});
    bool hit = container.CheckHitsWalls(0, particles);
    REQUIRE(hit == true);
  }

  SECTION("Hit right side wall") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(700, 350), vec2(1, 0)});
    bool hit = container.CheckHitsWalls(0, particles);
    REQUIRE(hit == true);
  }

  SECTION("Hit ceil") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(250, 500), vec2(0, 1)});
    bool hit = container.CheckHitsWalls(0, particles);
    REQUIRE(hit == true);
  }

  SECTION("Hit floor") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(250, 150), vec2(0, -1)});
    bool hit = container.CheckHitsWalls(0, particles);
    REQUIRE(hit == true);
  }
}

TEST_CASE("Particles Collisions Tests") {
  SECTION("opposite directional hit") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(250, 350), vec2(-1, 0)});
    particles.push_back({vec2(231, 350), vec2(1, 0)});
    vec2 expected_velocity_v1 = vec2(1,0);
    vec2 expected_velocity_v2 = vec2(-1, 0);
    bool hit = container.CheckTwoColliding(particles, 0, 1);
    vec2 actual_velocity_v1 = particles[0].second;
    vec2 actual_velocity_v2 = particles[1].second;
    REQUIRE(hit == true);
    REQUIRE(expected_velocity_v1 == actual_velocity_v1);
    REQUIRE(expected_velocity_v2 == actual_velocity_v2);
  }

  SECTION("same directional hit") {
    GasContainer container;
    vector<pair<vec2, vec2>> particles;
    particles.push_back({vec2(250, 350), vec2(0.5, 0)});
    particles.push_back({vec2(231, 350), vec2(1, 0)});
    vec2 expected_velocity_v1 = vec2(1,0);
    vec2 expected_velocity_v2 = vec2(0.5, 0);
    bool hit = container.CheckTwoColliding(particles, 0, 1);
    vec2 actual_velocity_v1 = particles[0].second;
    vec2 actual_velocity_v2 = particles[1].second;
    REQUIRE(hit == true);
    REQUIRE(expected_velocity_v1 == actual_velocity_v1);
    REQUIRE(expected_velocity_v2 == actual_velocity_v2);
  }
}
/*
TODO: Rename this test file. You'll also need to modify CMakeLists.txt.

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment and the placeholder test before submitting your code.
*/
