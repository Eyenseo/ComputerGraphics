#include "include/pyramid.hpp"

Pyramid::Pyramid() : Drawable() {}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z, double size
                   = 1) : Drawable(origin_x,
                                   origin_y,
                                   origin_z
                                   ) {
  set_size(size, size, size);
}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z,
                 double size_x, double size_y, double size_z) : Drawable(
    origin_x,
    origin_y,
    origin_z) {
  set_size(size_x, size_y, size_z);
}

Pyramid::~Pyramid() {}

void Pyramid::draw() const {
  double half_base_length = .5 * boundingbox_[0] / 2;

  Vec3 base_bottom_left  = Vec3(-half_base_length, -half_base_length, 0);
  Vec3 base_top_left     = Vec3(-half_base_length, half_base_length, 0);
  Vec3 base_top_right    = Vec3(half_base_length, half_base_length, 0);
  Vec3 base_bottom_right = Vec3(half_base_length, -half_base_length, 0);
  Vec3 top               = Vec3(0, 0, boundingbox_[2]);

  auto face
    = [](Vec3 v1, Vec3 v2, Vec3 v3) {
        Vec3 normal = (v2 - v1) % (v3 - v1);

        normal.Normalize();

        glNormal3dv(normal.p);
        glVertex3dv(v1.p);
        glVertex3dv(v2.p);
        glVertex3dv(v3.p);
      };


  SetMaterialColor(1, true);
  SetMaterialColor(2, false);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_.p[0],
              origin_.p[1], origin_.p[2]);

  glBegin(GL_TRIANGLES);
  //Base !!Counter clockwise from below!!
  face(base_top_right, base_bottom_right, base_bottom_left);
  face(base_bottom_left, base_top_left, base_top_right);
  //First Side
  face(base_bottom_right, top, base_bottom_left);
  //Second Side
  face(base_bottom_left, top, base_top_left);
  //Third Side
  face(base_top_left, top, base_top_right);
  //Fourth Side
  face(base_top_right, top, base_bottom_right);
  glEnd();

  glPopMatrix();
}

void Pyramid::set_size(double base_size, double height) {
  boundingbox_[0] = base_size;
  boundingbox_[1] = base_size;
  boundingbox_[2] = height;
}

void Pyramid::set_size(double x, double y, double z) {
  boundingbox_[0] = x;
  boundingbox_[1] = y;
  boundingbox_[2] = z;
}
