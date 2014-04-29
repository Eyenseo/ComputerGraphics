#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP value

#include <GL/gl.h>
#include <vector>

#include "gl_matrix.hpp"
#include "gl_vec.hpp"

class Drawable {
protected:

  GLVector<XYZW> origin_;
  GLVector<XYZ>  rotation_;
  GLVector<XYZ>  scale_;
  GLMatrix model_view;
  double*  color_;
  unsigned char colors_;

  Drawable();
  Drawable(double origin_x, double origin_y, double origin_z);
  Drawable(double origin_x, double origin_y, double origin_z,
           unsigned char colors);
  virtual ~Drawable();

  void set_material_color(int side, unsigned char color) const;
  void rotate_from(double x_angle, double y_angle, double z_angle,
                   double x_distance, double y_distance,
                   double z_distance) const;

public:

  virtual void                draw() = 0;

  virtual const GLVector<XYZW>get_origin() const;
  virtual void                set_origin(double origin_x, double origin_y,
                                         double origin_z);
  virtual void                set_origin(const GLVector<XYZW>& origin);

  virtual GLdouble            get_origin_x() const;
  virtual void                set_origin_x(double origin_x);

  virtual GLdouble            get_origin_y() const;
  virtual void                set_origin_y(double origin_y);

  virtual GLdouble            get_origin_z() const;
  virtual void                set_origin_z(double origin_z);

  virtual const GLVector<XYZ> get_rotation() const;

  virtual GLdouble            get_rotation_x() const;
  virtual void                set_rotation_x(double rotation);

  virtual GLdouble            get_rotation_y() const;
  virtual void                set_rotation_y(double rotation);

  virtual GLdouble            get_rotation_z() const;
  virtual void                set_rotation_z(double rotation);

  virtual const double*       get_color() const;
  virtual void                set_color(double r, double g, double b,
                                        unsigned char color);

  virtual double              get_color_red(unsigned char color) const;
  virtual void                set_color_red(double r, unsigned char color);

  virtual double              get_color_green(unsigned char color) const;
  virtual void                set_color_green(double g, unsigned char color);

  virtual double              get_color_blue(unsigned char color) const;
  virtual void                set_color_blue(double b, unsigned char color);

  virtual const GLVector<XYZ> get_scale() const;
  virtual void                set_scale(const GLVector<XYZ>& scale);
  virtual void                set_scale(double scale);
  virtual void                set_scale(double scale_x, double scale_y,
                                        double scale_z);

  virtual double              get_scale_x() const;
  virtual void                set_scale_x(double scale_x);

  virtual double              get_scale_y() const;
  virtual void                set_scale_y(double scale_y);

  virtual double              get_scale_z() const;
  virtual void                set_scale_z(double scale_z);
};
#endif // ifndef DRAWABLE_HPP
