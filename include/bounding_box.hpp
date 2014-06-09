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
      , origin_(nullptr) {
  }

public:
  BoundingBox(Hitable* h, GLVector<XYZW>* origin)
      : hitable_(h)
      , origin_(origin) {
  }

  virtual ~BoundingBox() {
  }
};
#endif
