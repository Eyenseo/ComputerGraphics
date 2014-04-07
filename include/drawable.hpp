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
  float*   color_;
  unsigned char colors_;

  Drawable();
  Drawable(float origin_x, float origin_y, float origin_z);
  Drawable(float origin_x, float origin_y, float origin_z,
           unsigned char colors);
  virtual ~Drawable();

  void set_material_color(int side, unsigned char color) const;
  void rotate_from(float x_angle, float y_angle, float z_angle,
                   float x_distance, float y_distance, float z_distance) const;

public:

  virtual void                draw() = 0;

  virtual const GLVector<XYZW>get_origin() const;
  virtual void                set_origin(float origin_x, float origin_y,
                                         float origin_z);
  virtual void                set_origin(const GLVector<XYZW>& origin);

  virtual GLfloat             get_origin_x() const;
  virtual void                set_origin_x(float origin_x);

  virtual GLfloat             get_origin_y() const;
  virtual void                set_origin_y(float origin_y);

  virtual GLfloat             get_origin_z() const;
  virtual void                set_origin_z(float origin_z);

  virtual const GLVector<XYZ> get_rotation() const;

  virtual GLfloat             get_rotation_x() const;
  virtual void                set_rotation_x(float rotation);

  virtual GLfloat             get_rotation_y() const;
  virtual void                set_rotation_y(float rotation);

  virtual GLfloat             get_rotation_z() const;
  virtual void                set_rotation_z(float rotation);

  virtual const float*        get_color() const;
  virtual void                set_color(float r, float g, float b,
                                        unsigned char color);

  virtual float               get_color_red(unsigned char color) const;
  virtual void                set_color_red(float r, unsigned char color);

  virtual float               get_color_green(unsigned char color) const;
  virtual void                set_color_green(float g, unsigned char color);

  virtual float               get_color_blue(unsigned char color) const;
  virtual void                set_color_blue(float b, unsigned char color);

  virtual const GLVector<XYZ> get_scale() const;
  virtual void                set_scale(const GLVector<XYZ>& scale);
  virtual void                set_scale(float scale);
  virtual void                set_scale(float scale_x, float scale_y,
                                        float scale_z);

  virtual float               get_scale_x() const;
  virtual void                set_scale_x(float scale_x);

  virtual float               get_scale_y() const;
  virtual void                set_scale_y(float scale_y);

  virtual float               get_scale_z() const;
  virtual void                set_scale_z(float scale_z);
};
#endif // ifndef DRAWABLE_HPP
