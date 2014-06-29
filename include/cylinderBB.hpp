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
  double radius_;
  double hight_;
  const double radius_orig_;

  CylinderBB()
      : BoundingBox(nullptr, nullptr)
      , radius_(1)
      , radius_orig_(1)
  	  , hight_(1){
  }

public:
  CylinderBB(Hitable* h, GLVector<XYZW>* origin, double radius, double hight)
      : BoundingBox(h, origin)
      , radius_(radius)
      , radius_orig_(radius)
  	  , hight_(hight) {
  }

  virtual ~CylinderBB() {
  }

  void update_scale(const GLVector<XYZ>& scale) {
    radius_ = radius_orig_ * scale[0];
  }
};




#endif /* CYLINDERBB_HPP_ */
