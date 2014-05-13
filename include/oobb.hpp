#ifndef OOBB_HPP
#define OOBB_HPP

#include "hitable.hpp"

class OOBB : public Hitable {
  friend Physic;

public:

  OOBB() {}

  virtual ~OOBB() {}
};
#endif // ifndef OOBB_HPP
