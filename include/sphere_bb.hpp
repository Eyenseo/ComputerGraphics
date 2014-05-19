#ifndef SPHERE_BB
#define SPHERE_BB

#include "hitable.hpp"

class SphereBB : public Hitable {
  friend Physic;


  SphereBB() {
  }

protected:
  double radius_;

public:
  SphereBB(GLVector<XYZW>* origin) : Hitable(origin) {
  }

  virtual ~SphereBB() {}
};
#endif // ifndef SPHERE_BB
