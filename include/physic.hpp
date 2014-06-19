#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <forward_list>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <chrono>

#include "gl_matrix.hpp"
#include "obb.hpp"
#include "sphere_bb.hpp"
#include "timer.hpp"

class Physic {
  std::forward_list<Hitable*>* hitables_;
  std::thread* col_t_;
  std::atomic<bool> end_;

  GLVector<XYZW> closest_point_on_OBB(const GLVector<XYZW>& a, const OBB& b);

 void collision();
  void collision(SphereBB& a, SphereBB& b);
  void collision(SphereBB& a, OBB& b);
  void collision(OBB& a, SphereBB& b);
  void collision(OBB& a, OBB& b);

public:
  Physic();
  Physic(std::forward_list<Hitable*>* hitables);
  ~Physic();

  void start();
  void stop();
};

#endif  // ifndef PHYSIC_HPP
