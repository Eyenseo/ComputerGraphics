#include "include/pyramid.hpp"

Pyramid::Pyramid()
  : Drawable() {}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z)
  : Drawable(origin_x, origin_y, origin_z) {}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z,
                 unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors)  {}

Pyramid::~Pyramid() {}

void Pyramid::draw() {
  GLVector<XYZW> base_bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> base_top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> base_top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> base_bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);
  GLVector<XYZW> top = GLVector<XYZW>(0, 0, 2, 1);

  auto face
    = [](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
         const GLVector<XYZW>& v3) {
        GLVector<XYZ> normal = (v2 - v1) % (v3 - v1);

        normal.Normalize();

        glNormal3dv(normal.get_vector());
        glVertex3dv(v1.get_vector());
        glVertex3dv(v2.get_vector());
        glVertex3dv(v3.get_vector());
      };

  set_material_color(1, 0);

  // glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0],
              origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  glBegin(GL_TRIANGLES);

  // Base !!Counter clockwise from below!!
  face(base_top_right, base_bottom_right, base_bottom_left);
  face(base_bottom_left,   base_top_left, base_top_right);

  // First Side
  face(base_bottom_right,            top, base_bottom_left);

  // Second Side
  face(base_bottom_left,             top, base_top_left);

  // Third Side
  face(base_top_left,                top, base_top_right);

  // Fourth Side
  face(base_top_right,               top, base_bottom_right);
  glEnd();

  glPopMatrix();
}
