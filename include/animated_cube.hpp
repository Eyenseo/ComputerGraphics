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

  double open_angel_;
  double closed_angel_;
  double current_angle_;
  double animation_time_;

  void calculate_current_angle();

public:

  AnimatedCube();
  AnimatedCube(double origin_x, double origin_y, double origin_z);
  AnimatedCube(double origin_x, double origin_y, double origin_z,
               unsigned char colors);
  ~AnimatedCube();

  virtual void draw();

  void         open();
  void         close();
};

#endif // ifndef ANIMATED_CUBE_HPP
