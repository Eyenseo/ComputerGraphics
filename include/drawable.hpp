#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP value

#include "vec3.hpp"
#include <GL/gl.h>

class Drawable {
protected:

  Vec3   origin_;
  float  rotation_[3];
  double boundingbox_[3];
  float  color_[6];
  float  scale_;

  Drawable();
  Drawable(double origin_x, double origin_y, double origin_z);

  void SetMaterialColor(int side, bool outside) const;
  void rotate_from(double x_angle, double y_angle,
                   double z_angle, double x_distance, double y_distance,
                   double z_distance) const;

  virtual void set_size(double x, double y, double z) = 0;

public:

  ~Drawable();

  virtual void         draw() = 0;

  virtual Vec3         get_origin() const;
  virtual void         set_origin(double origin_x,
                                  double origin_y,
                                  double origin_z);
  virtual void         set_origin(const Vec3& origin);

  virtual double       get_origin_x() const;
  virtual void         set_origin_x(double origin_x);

  virtual double       get_origin_y() const;
  virtual void         set_origin_y(double origin_y);

  virtual double       get_origin_z() const;
  virtual void         set_origin_z(double origin_z);

  virtual const double*get_boundingbox() const;

  virtual const float* get_rotation() const;

  virtual float        get_rotation_x() const;
  virtual void         set_rotation_x(float rotation);

  virtual float        get_rotation_y() const;
  virtual void         set_rotation_y(float rotation);

  virtual float        get_rotation_z() const;
  virtual void         set_rotation_z(float rotation);

  virtual const float* get_color();
  virtual void         set_color(float r, float g, float b,
                                 bool outside);

  virtual float        get_color_red(bool outside);
  virtual void         set_color_red(float r, bool outside);

  virtual float        get_color_green(bool outside);
  virtual void         set_color_green(float g, bool outside);

  virtual float        get_color_blue(bool outside);
  virtual void         set_color_blue(float b, bool outside);

  virtual void         set_scale(float scale);
  virtual float        get_scale();
};
#endif // ifndef DRAWABLE_HPP
