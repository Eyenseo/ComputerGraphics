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

protected:

  virtual void set_size(double x, double y, double z);

public:

  AnimatedCube();
  AnimatedCube(double origin_x, double origin_y, double origin_z, double size);
  AnimatedCube(double origin_x, double origin_y, double origin_z, double size_x,
               double size_y, double size_z);
  ~AnimatedCube();

  virtual void draw();
  virtual void set_size(double size);

  void         open();
  void         close();
};

#endif // ifndef ANIMATED_CUBE_HPP
