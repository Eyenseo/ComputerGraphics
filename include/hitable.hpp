#ifndef HITABLE_HPP
#define HITABLE_HPP

#include "gl_vec.hpp"

class Physic;
class Hitable {
  friend Physic;

protected:

  GLVector<XYZW>* origin_;
  GLVector<XYZW>  speed_;
  double fraction_ = 0.005;

  Hitable() : origin_(nullptr) {}

public:

  Hitable(GLVector<XYZW>* origin) : origin_(origin) {}

  virtual ~Hitable() {}

  void add_speed(const GLVector<XYZW>& add) {
    speed_ += add;
  }
};
#endif // ifndef HITABLE_HPP
