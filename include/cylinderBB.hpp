/*
 * cylinderBB.hpp
 *
 *  Created on: 24.06.2014
 *      Author: Ahmed
 */

#ifndef CYLINDERBB_HPP_
#define CYLINDERBB_HPP_
#include "bounding_box.hpp"

class Physic;
class CylinderBB : public BoundingBox {
  friend Physic;


protected:
  const double radius_orig_;
  double radius_;
  const double half_height_orig_;
  double half_height_;
  GLVector<XYZW> axis_;

  CylinderBB()
      : BoundingBox(nullptr, nullptr)
      , radius_orig_(.5)
      , radius_(.5)
      , half_height_orig_()
      , half_height_()
      , axis_(GLVector<XYZW>::ZVec) {
  }

public:
  CylinderBB(Hitable* h, GLVector<XYZW>* origin, double radius, double height)
      : BoundingBox(h, origin)
      , radius_orig_(radius)
      , radius_(radius)
      , half_height_orig_(height)
      , half_height_(half_height_orig_)
      , axis_(GLVector<XYZW>::ZVec) {
  }

  virtual ~CylinderBB() {
  }

  void update_scale(const GLVector<XYZ>& scale) {
    radius_ = radius_orig_ * scale[0];
    half_height_ = half_height_orig_ * scale[2];
  }

  void update_rotation(const GLMatrix& xyz) {
    axis_ = xyz * GLVector<XYZW>::ZVec;
  }

  void update_rotation(const GLVector<XYZ>& rotation) {
#ifndef M_PI
#define M_PI 3.14159265359
#endif
    static const double to_rad = 1.0 / 180.0 * M_PI;

    GLMatrix mx;
    mx.set_data(0, 0, 1);
    mx.set_data(1, 1, cos(rotation[0] * to_rad));
    mx.set_data(1, 2, sin(rotation[0] * to_rad));
    mx.set_data(2, 2, mx.get_data(1, 1));
    mx.set_data(2, 1, -mx.get_data(1, 2));
    mx.set_data(3, 3, 1);

    GLMatrix my;
    my.set_data(0, 0, cos(rotation[1] * to_rad));
    my.set_data(0, 2, -sin(rotation[1] * to_rad));
    my.set_data(1, 1, 1);
    my.set_data(2, 0, -my.get_data(0, 2));
    my.set_data(2, 2, my.get_data(0, 0));
    my.set_data(3, 3, 1);

    GLMatrix mz;
    mz.set_data(0, 0, cos(rotation[2] * to_rad));
    mz.set_data(0, 1, sin(rotation[2] * to_rad));
    mz.set_data(1, 0, -mz.get_data(0, 1));
    mz.set_data(1, 1, mz.get_data(0, 0));
    mz.set_data(2, 2, 1);
    mz.set_data(3, 3, 1);

    update_rotation(mz * my * mx);
  }
};
#endif
