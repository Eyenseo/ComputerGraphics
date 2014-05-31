#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include "gl_vec.hpp"

class Hitable;
class Physic;
class BoundingBox {
  friend Physic;

protected:
  Hitable* hitable_;
  GLVector<XYZW>* origin_;

  BoundingBox()
      : hitable_(nullptr)
      , origin_(nullptr)
      , collide_(true) {
  }

public:
  bool collide_;

  BoundingBox(Hitable* h, GLVector<XYZW>* origin)
      : hitable_(h)
      , origin_(origin)
      , collide_(true) {
  }

  virtual ~BoundingBox() {
  }
};
#endif
