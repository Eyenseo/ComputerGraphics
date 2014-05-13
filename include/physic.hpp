#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <forward_list>

#include "gl_matrix.hpp"
#include "oobb.hpp"
#include "sphere_bb.hpp"

class Physic {
public:

  Physic();
  ~Physic();

  void collision(std::forward_list<Hitable*>objects);
  void collision(SphereBB& a, SphereBB& b);
  void collision(SphereBB& a, OOBB& b);
  void collision(OOBB& a, SphereBB& b);
  void collision(OOBB& a, OOBB& b);
};

#endif // ifndef PHYSIC_HPP
