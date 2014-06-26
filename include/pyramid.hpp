#ifndef PYRAMID_HPP
#define PYRAMID_HPP

#include "drawable.hpp"
#include "hitable.hpp"
#include "sphere_bb.hpp"

class Pyramid : public Drawable, public Hitable {
protected:
  SphereBB* sb_;
  GLVector<XYZW>& origin_ = Drawable::origin_;

public:
  Pyramid();
  Pyramid(double origin_x, double origin_y, double origin_z);
  Pyramid(double origin_x, double origin_y, double origin_z,
          unsigned char colors);
  ~Pyramid();

  virtual void draw();
  virtual void step();
};

#endif  // ifndef PYRAMID_HPP
