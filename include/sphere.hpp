#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"

class Sphere : public Drawable {
protected:

  virtual void set_size(double x, double y, double z);

public:

  Sphere();
  Sphere(double origin_x, double origin_y, double origin_z, double size);
  Sphere(double origin_x, double origin_y, double origin_z, double size_x,
         double size_y, double size_z);
  ~Sphere();

  virtual void draw() const;
  virtual void set_size(double radius);
};


#endif //ifndef SPHERE_HPP
