#include "include/cube.hpp"

#include <sstream>

Cube::Cube()
    : Drawable()
    , Hitable()
    , obb_(this, &(Drawable::origin_), GLVector<XYZ>(0.5, 0.5, 0.5)) {
  add_bounding_box(&obb_);
}

Cube::Cube(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z)
    , Hitable()
    , obb_(this, &(Drawable::origin_), GLVector<XYZ>(0.5, 0.5, 0.5)) {
  add_bounding_box(&obb_);
}

Cube::Cube(double origin_x, double origin_y, double origin_z,
           unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable()
    , obb_(this, &(Drawable::origin_), GLVector<XYZ>(0.5, 0.5, 0.5)) {
  add_bounding_box(&obb_);
}

Cube::~Cube() {}

void Cube::step() {
   if(moveable_) {
    //TODO review slow speeds are a problem on edges
    speed_ = speed_ + (GLVector<XYZW>::ZVec * (-9.81 * 0.005))
             - (speed_ * fraction_);
    origin_ += speed_ * 0.16;
  }
}

void Cube::draw() {
  GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

  auto face = [&](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
                  const GLVector<XYZW>& v3, const GLVector<XYZW>& v4) {
    GLVector<XYZ> normal = (const GLVector<XYZ>)(v2 - v1)
                           % (const GLVector<XYZ>)(v3 - v1);

    glBegin(GL_QUADS);
    normal.Normalize();
    glNormal3dv(normal);
    glVertex3dv(v1);
    glVertex3dv(v2);
    glVertex3dv(v3);
    glVertex3dv(v4);
    glEnd();
  };

  set_material_color(1, 0);

  // glEnable(GL_RESCALE_NORMAL); // TODO Needed?
  glMatrixMode(GL_MODELVIEW);
  rotate_from(rotation_[0], rotation_[1], rotation_[2],
              origin_[0], origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  // Bottom
  rotate_from(0, 0, 0, 0, 0, -.5);
  face(top_left, top_right, bottom_right, bottom_left);

  // Top
  glPopMatrix();
  rotate_from(180, 0, 0, 0, 0, .5);
  face(top_left, top_right, bottom_right, bottom_left);

  // Left
  glPopMatrix();
  rotate_from(0, 90, 0, -.5, 0, 0);
  face(top_left, top_right, bottom_right, bottom_left);

  // Back
  glPopMatrix();
  rotate_from(90, 0, 0, 0, .5, 0);
  face(top_left, top_right, bottom_right, bottom_left);

  // Right
  glPopMatrix();
  rotate_from(0, 270, 0, .5, 0, 0);
  face(top_left, top_right, bottom_right, bottom_left);

  // Top
  glPopMatrix();
  rotate_from(90, 180, 0, 0, -.5, 0);
  face(top_left, top_right, bottom_right, bottom_left);

  glPopMatrix();
  glPopMatrix();
}

void Cube::set_rotation(const GLVector<XYZ>& rotation) {
  Drawable::set_rotation(rotation);
  obb_.update_rotation(rotation_);
}

void Cube::set_rotation(double rotation_x, double rotation_y,
                        double rotation_z) {
  Drawable::set_rotation(rotation_x, rotation_y, rotation_z);
  obb_.update_rotation(rotation_);
}

void Cube::set_rotation_x(double rotation) {
  Drawable::set_rotation_x(rotation);
  obb_.update_rotation(rotation_);
}

void Cube::set_rotation_y(double rotation) {
  Drawable::set_rotation_y(rotation);
  obb_.update_rotation(rotation_);
}

void Cube::set_rotation_z(double rotation) {
  Drawable::set_rotation_z(rotation);
  obb_.update_rotation(rotation_);
}

void Cube::set_scale(const GLVector<XYZ>& scale) {
  Drawable::set_scale(scale);
  obb_.update_scale(scale_);
}

void Cube::set_scale(double scale) {
  Drawable::set_scale(scale);
  obb_.update_scale(scale_);
}

void Cube::set_scale(double scale_x, double scale_y, double scale_z) {
  Drawable::set_scale(scale_x, scale_y, scale_z);
  obb_.update_scale(scale_);
}

void Cube::set_scale_x(double scale_x) {
  Drawable::set_scale_x(scale_x);
  obb_.update_scale(scale_);
}

void Cube::set_scale_y(double scale_y) {
  Drawable::set_scale_y(scale_y);
  obb_.update_scale(scale_);
}

void Cube::set_scale_z(double scale_z) {
  Drawable::set_scale_z(scale_z);
  obb_.update_scale(scale_);
}
