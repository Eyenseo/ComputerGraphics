#ifndef PYRAMID_HPP
#define PYRAMID_HPP value

#include "drawable.hpp"

class Pyramid : public Drawable {
protected:

  virtual void set_size(double x, double y, double z);

public:

  Pyramid();
  Pyramid(double origin_x, double origin_y, double origin_z, double size);
  Pyramid(double origin_x, double origin_y, double origin_z, double size_x,
          double size_y, double size_z);
  ~Pyramid();

  virtual void draw();
  virtual void set_size(double base_size, double height);
};

#endif // ifndef PYRAMID_HPP
