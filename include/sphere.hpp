#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"

class Sphere : public Drawable {
  static const GLVector<XYZW> XVec;
  static const GLVector<XYZW> YVec;
  static const GLVector<XYZW> ZVec;

public:

  double fraction_ = 0.005;
  GLVector<XYZW>  speed;
  GLVector<XYZW>& origin_ = Drawable::origin_;

  Sphere();
  Sphere(double origin_x, double origin_y, double origin_z);
  Sphere(double origin_x, double origin_y, double origin_z,
         unsigned char colors);
  ~Sphere();

  virtual void draw();
};

#endif // ifndef SPHERE_HPP
