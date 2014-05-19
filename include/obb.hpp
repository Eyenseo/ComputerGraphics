#ifndef OBB_HPP
#define OBB_HPP

#include "hitable.hpp"
#include "gl_vec.hpp"

class OBB : public Hitable {
  friend Physic;

protected:
  GLVector<XYZW> local_axis_[3];
  GLVector<XYZW> half_length_;

  OBB() : Hitable()  {}
public:

  OBB(GLVector<XYZW>* origin) : Hitable(origin) {}

  virtual ~OBB() {}
};
#endif // ifndef OBB_HPP
