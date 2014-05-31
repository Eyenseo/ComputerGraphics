#include "include/drawable.hpp"

#include <assert.h>
#include <iostream>
#include <sstream>

Drawable::Drawable()
  : origin_(0, 0, 0, 1),
  scale_(1, 1, 1),
  color_(new double[1 * 3]()),
  colors_(1) {}

Drawable::Drawable(double origin_x, double origin_y, double origin_z)
  : origin_(origin_x, origin_y, origin_z, 1),
  scale_(1, 1, 1),
  color_(new double[1 * 3]()),
  colors_(1)  {}

Drawable::Drawable(double origin_x, double origin_y, double origin_z,
                   unsigned char colors)
  : origin_(origin_x, origin_y, origin_z, 1),
  scale_(1, 1, 1),
  color_(new double[colors * 3]()),
  colors_(colors)  {}

Drawable::~Drawable() {
  delete[]color_;
}

/**
 * The function will set the material color for OpenGL
 *
 * @param side    1 = front color, 2 = back color, else both
 * @param outside which color to be used for the chosen side
 */
void Drawable::set_material_color(int side, unsigned char color = 0) const {
  assert(color < colors_);
  float amb[4], dif[4], spe[4];
  int   mat, c = color * 3;

  dif[0] = color_[c];
  dif[1] = color_[c + 1];
  dif[2] = color_[c + 2];

  for(int i = 0; i < 3; i++) {
    amb[i] = .1 * dif[i];
    spe[i] = .5;
  }
  amb[3] = dif[3] = spe[3] = 1.0;

  switch(side) {
    case 1: mat = GL_FRONT;
      break;
    case 2: mat = GL_BACK;
      break;
    default: mat = GL_FRONT_AND_BACK;
  }

  glMaterialfv(mat, GL_AMBIENT,  amb);
  glMaterialfv(mat, GL_DIFFUSE,  dif);
  glMaterialfv(mat, GL_SPECULAR, spe);
  glMaterialf(mat, GL_SHININESS, 20);
}

/**
 * The function will first translate and then rotate the modelview matrix
 *
 * @param x_angle    angel to rotate around the x-axis
 * @param y_angle    angle to rotate around the y-axis
 * @param z_angle    angle to rotate around the z-axis
 * @param x_distance distance the origin has to move in x direction before
 *                   rotation
 * @param y_distance distance the origin has to move in y direction before
 *                   rotation
 * @param z_distance distance the origin has to move in z direction before
 *                   rotation
 */
void Drawable::rotate_from(double x_angle, double y_angle, double z_angle,
                           double x_distance, double y_distance,
                           double z_distance) const {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(x_distance, y_distance, z_distance);
  glRotatef(x_angle, 1,    0.0f, 0.0f);
  glRotatef(y_angle, 0.0f, 1,    0.0f);
  glRotatef(z_angle, 0.0f, 0.0f,    1);
}

const GLVector<XYZW>Drawable::get_origin() const {
  return origin_;
}

void Drawable::set_origin(const GLVector<XYZW>& origin) {
  origin_ = GLVector<XYZW>(origin);
}

void Drawable::set_origin(double origin_x, double origin_y, double origin_z) {
  origin_ = GLVector<XYZW>(origin_x, origin_y, origin_z, 1);
}

double Drawable::get_origin_x() const {
  return origin_[0];
}

void Drawable::set_origin_x(double origin_x) {
  origin_[0] = origin_x;
}

double Drawable::get_origin_y() const {
  return origin_[1];
}

void Drawable::set_origin_y(double origin_y) {
  origin_[1] = origin_y;
}

double Drawable::get_origin_z() const {
  return origin_[2];
}

void Drawable::set_origin_z(double origin_z) {
  origin_[2] = origin_z;
}

const GLVector<XYZ> Drawable::get_rotation() const {
  return rotation_;
}

void Drawable::set_rotation(const GLVector<XYZ>& rotation) {
  rotation_ = GLVector<XYZ>(rotation);
}

void Drawable::set_rotation(double rotation_x, double rotation_y,
                            double rotation_z) {
  rotation_[0] = rotation_x;
  rotation_[1] = rotation_y;
  rotation_[2] = rotation_z;
}

GLdouble Drawable::get_rotation_x() const {
  return rotation_[0];
}

void Drawable::set_rotation_x(double rotation_x) {
  rotation_[0] = rotation_x;
}

GLdouble Drawable::get_rotation_y() const {
  return rotation_[1];
}

void Drawable::set_rotation_y(double rotation_y) {
  rotation_[1] = rotation_y;
}

GLdouble Drawable::get_rotation_z() const {
  return rotation_[2];
}

void Drawable::set_rotation_z(double rotation_z) {
  rotation_[2] = rotation_z;
}

const double* Drawable::get_color() const {
  return color_;
}

void Drawable::set_color(double r, double g, double b, unsigned char color
                           = 0) {
  assert(color < colors_);

  int i = color * 3;

  if(r > 1) {
    color_[i] = r / 255;
  } else {
    color_[i] = r;
  }
  if(g > 1) {
    color_[i + 1] = g / 255;
  } else {
    color_[i + 1] = g;
  }
  if(b > 1) {
    color_[i + 2] = b / 255;
  } else {
    color_[i + 2] = b;
  }
}

double Drawable::get_color_red(unsigned char color = 0) const {
  return color_[color * 3];
}

void Drawable::set_color_red(double r, unsigned char color = 0) {
  assert(color < colors_);

  if(r > 1) {
    color_[color * 3] = r / 255;
  } else {
    color_[color * 3] = r;
  }
}

double Drawable::get_color_green(unsigned char color = 0) const {
  return color_[color * 3 + 1];
}

void Drawable::set_color_green(double g, unsigned char color = 0) {
  assert(color < colors_);

  if(g > 1) {
    color_[color * 3 + 1] = g / 255;
  } else {
    color_[color * 3 + 1] = g;
  }
}

double Drawable::get_color_blue(unsigned char color = 0) const {
  return color_[color * 3 + 2];
}

void Drawable::set_color_blue(double b, unsigned char color = 0) {
  assert(color < colors_);

  if(b > 1) {
    color_[color * 3 + 2] = b / 255;
  } else {
    color_[color * 3 + 2] = b;
  }
}

const GLVector<XYZ>Drawable::get_scale() const {
  return scale_;
}

void Drawable::set_scale(double scale_x, double scale_y, double scale_z) {
  scale_[0] = scale_x;
  scale_[1] = scale_y;
  scale_[2] = scale_z;
}

void Drawable::set_scale(const GLVector<XYZ>& scale) {
  scale_[0] = scale[0];
  scale_[1] = scale[1];
  scale_[2] = scale[2];
}

void Drawable::set_scale(double scale) {
  scale_[0] = scale;
  scale_[1] = scale;
  scale_[2] = scale;
}

double Drawable::get_scale_x() const {
  return scale_[0];
}

void Drawable::set_scale_x(double scale_x) {
  scale_[0] = scale_x;
}

double Drawable::get_scale_y() const {
  return scale_[1];
}

void Drawable::set_scale_y(double scale_y) {
  scale_[1] = scale_y;
}

double Drawable::get_scale_z() const {
  return scale_[2];
}

void Drawable::set_scale_z(double scale_z) {
  scale_[2] = scale_z;
}
