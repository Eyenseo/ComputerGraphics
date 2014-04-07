#ifndef CUBE_HPP
#define CUBE_HPP value

#include "drawable.hpp"

class Cube : public Drawable {
public:

  Cube();
  Cube(float origin_x, float origin_y, float origin_z);
  Cube(float origin_x, float origin_y, float origin_z, unsigned char colors);
  ~Cube();

  virtual void draw();
};

#endif // ifndef CUBE_HPP
