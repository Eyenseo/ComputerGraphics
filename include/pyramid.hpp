#ifndef PYRAMID_HPP
#define PYRAMID_HPP value

#include "drawable.hpp"

class Pyramid : public Drawable {
public:

  Pyramid();
  Pyramid(float origin_x, float origin_y, float origin_z);
  Pyramid(float origin_x, float origin_y, float origin_z, unsigned char colors);
  ~Pyramid();

  virtual void draw();
};

#endif // ifndef PYRAMID_HPP
