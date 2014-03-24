#include "include/cube.hpp"

Cube::Cube() : Drawable() {}

Cube::Cube(double origin_x, double origin_y, double origin_z, double size
             = 1)  :
  Drawable(origin_x, origin_y, origin_z) {
  set_size(size, size, size);
}

Cube::Cube(double origin_x, double origin_y, double origin_z, double size_x,
           double size_y, double size_z)  :
  Drawable(origin_x, origin_y, origin_z) {
  set_size(size_x, size_y, size_z);
}

Cube::~Cube() {}

void Cube::draw() {
  double half_length = .5 * boundingbox_[0];

  Vec3 bottom_left  = Vec3(-half_length, -half_length, 0);
  Vec3 top_left     = Vec3(-half_length, half_length, 0);
  Vec3 top_right    = Vec3(half_length, half_length, 0);
  Vec3 bottom_right = Vec3(half_length, -half_length, 0);

  auto face
    = [](const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& v4) {
        Vec3 normal = (v2 - v1) % (v3 - v1);

        normal.Normalize();

        glNormal3dv(normal.p);
        glVertex3dv(v1.p);
        glVertex3dv(v2.p);
        glVertex3dv(v3.p);
        glVertex3dv(v4.p);
      };

  SetMaterialColor(1, true);
  SetMaterialColor(2, false);

  glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_.p[0],
              origin_.p[1], origin_.p[2]);
  glScalef(scale_, scale_, scale_);

  // Bottom
  rotate_from(0, 0, 0, 0, 0, -half_length);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Top
  glPopMatrix();
  rotate_from(180, 0, 0, 0, 0, half_length);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Left
  glPopMatrix();
  rotate_from(0, 90, 0, -half_length, 0, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Back
  glPopMatrix();
  rotate_from(90, 0, 0, 0, half_length, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Right
  glPopMatrix();
  rotate_from(0, 270, 0, half_length, 0, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Top
  glPopMatrix();
  rotate_from(90, 180, 0, 0, -half_length, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  glPopMatrix();
  glPopMatrix();
}

void Cube::set_size(double size) {
  boundingbox_[0] = size;
  boundingbox_[1] = size;
  boundingbox_[2] = size;
}

void Cube::set_size(double x, double y, double z) {
  boundingbox_[0] = x;
  boundingbox_[1] = y;
  boundingbox_[2] = z;
}
