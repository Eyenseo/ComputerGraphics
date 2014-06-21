
#ifndef SPHERE_HPP
#define SPHERE_HPP value

#include "drawable.hpp"
#include "hitable.hpp"
#include "sphere_bb.hpp"

class Sphere : public Drawable, public Hitable {


protected:
  GLVector<XYZW>& origin_ = Drawable::origin_;

  const int resolution_;
  const int vertices_size_;
  const int normals_size_;
  GLuint vboID_;
  SphereBB* sb_;
  GLfloat* vertices_;
  GLfloat* normals_;

  void update_geometry();
  void load_shader(const char* filename, GLuint& vertexShader, bool vertex);

public:
  Sphere();
  Sphere(double origin_x, double origin_y, double origin_z);
  Sphere(double origin_x, double origin_y, double origin_z,
         unsigned char colors);
  ~Sphere();

  virtual void draw();
  virtual void step();

  virtual void set_scale(const GLVector<XYZ>& scale);
  virtual void set_scale(double scale);
  virtual void set_scale(double scale_x, double scale_y, double scale_z);
  virtual void set_scale_x(double scale_x);
  virtual void set_scale_y(double scale_y);
  virtual void set_scale_z(double scale_z);
};

#endif  // ifndef SPHERE_HPP
