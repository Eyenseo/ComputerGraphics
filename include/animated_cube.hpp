#ifndef ANIMATED_CUBE_HPP
#define ANIMATED_CUBE_HPP

#include "include/cube.hpp"
#include <math.h>

#include <iostream>

class AnimatedCube : public Cube {
  enum State {
    OPENING,
    CLOSING,
    OPEN,
    CLOSED
  };

  State state_;

  float open_angel_;
  float closed_angel_;
  float current_angle_;
  float animation_time_;

  void calculate_current_angle();

public:

  AnimatedCube();
  AnimatedCube(float origin_x, float origin_y, float origin_z);
  AnimatedCube(float origin_x, float origin_y, float origin_z,
               unsigned char colors);
  ~AnimatedCube();

  virtual void draw();

  void         open();
  void         close();
};

#endif // ifndef ANIMATED_CUBE_HPP
