#ifndef PYRAMID_HPP
#define PYRAMID_HPP value

#include "drawable.hpp"

class Pyramid : public Drawable {
public:

  Pyramid();
  Pyramid(double origin_x, double origin_y, double origin_z);
  Pyramid(double origin_x, double origin_y, double origin_z,
          unsigned char colors);
  ~Pyramid();

  virtual void draw();
};

#endif // ifndef PYRAMID_HPP
