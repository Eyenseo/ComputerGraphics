#ifndef CUBE_HPP
#define CUBE_HPP value

#include "drawable.hpp"

class Cube : public Drawable {
public:

  Cube();
  Cube(double origin_x, double origin_y, double origin_z);
  Cube(double origin_x, double origin_y, double origin_z, unsigned char colors);
  ~Cube();

  virtual void draw();
};

#endif // ifndef CUBE_HPP
