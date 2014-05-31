#ifndef SPHERE_BB
#define SPHERE_BB

#include "bounding_box.hpp"

class Physic;
class SphereBB : public BoundingBox {
  friend Physic;


protected:
  double radius_;
  const double radius_orig_;

  SphereBB()
      : BoundingBox(nullptr, nullptr)
      , radius_(1)
      , radius_orig_(1) {
  }

public:
  SphereBB(Hitable* h, GLVector<XYZW>* origin, double radius)
      : BoundingBox(h, origin)
      , radius_(radius)
      , radius_orig_(radius) {
  }

  virtual ~SphereBB() {
  }

  void update_scale(const GLVector<XYZ>& scale) {
    radius_ = radius_orig_ * scale[0];
  }
};
#endif  // ifndef SPHERE_BB
