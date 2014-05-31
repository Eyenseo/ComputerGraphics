#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"
#include "hitable.hpp"
#include "sphere_bb.hpp"

class Sphere : public Drawable, public Hitable {
protected:
  SphereBB* sb_;
  GLVector<XYZW>& origin_ = Drawable::origin_;

public:

  Sphere();
  Sphere(double origin_x, double origin_y, double origin_z);
  Sphere(double origin_x, double origin_y, double origin_z,
         unsigned char colors);
  ~Sphere();

  virtual void draw();
  virtual void step();

  virtual void set_scale(const GLVector<XYZ>& scale);
  virtual void set_scale(double scale);
  virtual void set_scale(double scale_x, double scale_y, double scale_z);
  virtual void set_scale_x(double scale_x);
  virtual void set_scale_y(double scale_y);
  virtual void set_scale_z(double scale_z);
};

#endif // ifndef SPHERE_HPP
