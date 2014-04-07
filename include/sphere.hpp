#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"

class Sphere : public Drawable {
  static const GLVector<XYZW> XVec;
  static const GLVector<XYZW> YVec;
  static const GLVector<XYZW> ZVec;

public:

  Sphere();
  Sphere(float origin_x, float origin_y, float origin_z);
  Sphere(float origin_x, float origin_y, float origin_z, unsigned char colors);
  ~Sphere();

  virtual void draw();
};

#endif // ifndef SPHERE_HPP
