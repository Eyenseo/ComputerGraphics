#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <forward_list>

#include "gl_matrix.hpp"
#include "obb.hpp"
#include "sphere_bb.hpp"

class Physic {
  GLVector<XYZW> closest_point_on_OBB(const GLVector<XYZW>& a, const OBB& b);
  std::forward_list<Hitable*>* hitables_;

public:

  Physic();
  Physic(std::forward_list<Hitable*>* hitables);
  ~Physic();

  void collision(Hitable* h);
  void collision(SphereBB& a, SphereBB& b);
  void collision(SphereBB& a, OBB& b);
  void collision(OBB& a, SphereBB& b);
  void collision(OBB& a, OBB& b);
};

#endif // ifndef PHYSIC_HPP
