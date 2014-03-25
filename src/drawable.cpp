#include "include/drawable.hpp"

#include <iostream>

Drawable::Drawable()
  : origin_(0, 0, 0),
  boundingbox_{0, 0, 0},
  color_{1, 0, 1, 1, 0, 1},
  scale_(1) {}

Drawable::Drawable(double origin_x, double origin_y, double origin_z)
  : origin_(origin_x, origin_y, origin_z),
  color_{1, 0, 1, 1, 0, 1},
  scale_(1) {}

Drawable::~Drawable() {}

/**
 * The function will set the material color for OpenGL
 *
 * @param side    1 = front color, 2 = back color, else both
 * @param outside which color to be used for the chosen side
 */
void Drawable::SetMaterialColor(int side, bool outside = true) const {
  float amb[4], dif[4], spe[4];
  int   mat, c = outside ? 0 : 3;

  dif[0] = color_[c++];
  dif[1] = color_[c++];
  dif[2] = color_[c];

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

Vec3 Drawable::get_origin() const {
  return origin_;
}

void Drawable::set_origin(const Vec3& origin) {
  origin_ = Vec3(origin);
}

void Drawable::set_origin(double origin_x, double origin_y, double origin_z) {
  origin_ = Vec3(origin_x, origin_y, origin_z);
}

double Drawable::get_origin_x() const {
  return origin_.p[0];
}

void Drawable::set_origin_x(double origin_x) {
  origin_.p[0] = origin_x;
}

double Drawable::get_origin_y() const {
  return origin_.p[1];
}

void Drawable::set_origin_y(double origin_y) {
  origin_.p[1] = origin_y;
}

double Drawable::get_origin_z() const {
  return origin_.p[2];
}

void Drawable::set_origin_z(double origin_z) {
  origin_.p[2] = origin_z;
}

const double*Drawable::get_boundingbox() const {
  return boundingbox_;
}

const float*Drawable::get_rotation() const {
  return rotation_;
}

float Drawable::get_rotation_x() const {
  return rotation_[0];
}

void Drawable::set_rotation_x(float rotation_x) {
  rotation_[0] = rotation_x;
}

float Drawable::get_rotation_y() const {
  return rotation_[1];
}

void Drawable::set_rotation_y(float rotation_y) {
  rotation_[0] = rotation_y;
}

float Drawable::get_rotation_z() const {
  return rotation_[2];
}

void Drawable::set_rotation_z(float rotation_z) {
  rotation_[2] = rotation_z;
}

const float*Drawable::get_color() {
  return color_;
}

void Drawable::set_color(float r, float g, float b, bool outside = true) {
  int i = outside ? 0 : 3;

  color_[i++] = r;
  color_[i++] = g;
  color_[i]   = b;
}

float Drawable::get_color_red(bool outside = true) {
  return color_[outside ? 0 : 3];
}

void Drawable::set_color_red(float r, bool outside = true) {
  color_[outside ? 0 : 3] = r;
}

float Drawable::get_color_green(bool outside = true) {
  return color_[outside ? 1 : 4];
}

void Drawable::set_color_green(float g, bool outside = true) {
  color_[outside ? 1 : 4] = g;
}

float Drawable::get_color_blue(bool outside = true) {
  return color_[outside ? 2 : 5];
}

void Drawable::set_color_blue(float b, bool outside = true) {
  color_[outside ? 2 : 5] = b;
}

void Drawable::set_scale(float scale) {
  scale_ = scale;
}

float Drawable::get_scale() {
  return scale_;
}
