#ifndef SPHERE_BB
#define SPHERE_BB

#include "hitable.hpp"

class SphereBB : public Hitable {
  friend Physic;

  double radius_;

  SphereBB() {}

public:

  SphereBB(GLVector<XYZW>* origin) : Hitable(origin) {}

  virtual ~SphereBB() {}
};
#endif // ifndef SPHERE_BB
