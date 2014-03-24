#ifndef CUBE_HPP
#define CUBE_HPP value

#include "drawable.hpp"

class Cube : public Drawable {
protected:

  virtual void set_size(double x, double y, double z);

public:

  Cube();
  Cube(double origin_x, double origin_y, double origin_z, double size);
  Cube(double origin_x, double origin_y, double origin_z, double size_x,
       double size_y, double size_z);
  ~Cube();

  virtual void draw();
  virtual void set_size(double size);
};

#endif // ifndef CUBE_HPP
