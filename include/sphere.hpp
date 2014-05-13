#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"
#include "sphere_bb.hpp"

class Sphere : public Drawable, public SphereBB {
  static const GLVector<XYZW> XVec;
  static const GLVector<XYZW> YVec;
  static const GLVector<XYZW> ZVec;

protected:

  GLVector<XYZW>& origin_ = Drawable::origin_;

public:

  Sphere();
  Sphere(double origin_x, double origin_y, double origin_z);
  Sphere(double origin_x, double origin_y, double origin_z,
         unsigned char colors);
  ~Sphere();

  virtual void draw();
};

#endif // ifndef SPHERE_HPP
