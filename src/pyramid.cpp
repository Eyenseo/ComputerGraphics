#include "include/pyramid.hpp"

Pyramid::Pyramid()
    : Drawable()
    , Hitable() {
}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z)
    , Hitable() {
  sb_ = new SphereBB(this, &origin_, .1);
  add_bounding_box(sb_);
}

Pyramid::Pyramid(double origin_x, double origin_y, double origin_z,
                 unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable() {
  sb_ = new SphereBB(this, &origin_, .1);
  add_bounding_box(sb_);
}

Pyramid::~Pyramid() {
}

void Pyramid::step() {
  set_rotation_z(get_rotation_z() + 0.5);
}

void Pyramid::draw() {
  static const GLVector<XYZW> base_bottom_left = GLVector<XYZW>(-.5, -.5, 0, 1);
  static const GLVector<XYZW> base_top_left = GLVector<XYZW>(-.5, .5, 0, 1);
  static const GLVector<XYZW> base_top_right = GLVector<XYZW>(.5, .5, 0, 1);
  static const GLVector<XYZW> base_bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);
  static const GLVector<XYZW> top = GLVector<XYZW>(0, 0, 2, 1);
  static const GLVector<XYZW> e1
      = (const GLVector<XYZ>)(base_bottom_right - base_top_left)
        % (const GLVector<XYZ>)(top - base_top_left);
  static const GLVector<XYZW> e2
      = (const GLVector<XYZ>)(base_top_right - base_bottom_left)
        % (const GLVector<XYZ>)(top - base_bottom_left);

  auto line = [](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
                 const GLVector<XYZW>& v3) {
    GLVector<XYZ> normal = (const GLVector<XYZ>)(v2 - v1)
                           % (const GLVector<XYZ>)(v3 - v1);

    normal.Normalize();

    glNormal3dv(normal.get_vector());
    glVertex3dv(v1.get_vector());
    glVertex3dv(v2.get_vector());
  };

  set_material_color(1, 0);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_NORMALIZE);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0], origin_[1],
              origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  glBegin(GL_LINES);
  // glBegin(GL_TRIANGLES);

  // Base !!Counter clockwise from below!!
  line(base_top_right, base_bottom_right, base_bottom_left);
  line(base_top_left, base_top_right, base_bottom_right);
  line(base_bottom_left, base_top_left, base_top_right);
  line(base_bottom_right, base_bottom_left, base_top_left);

  // First Side
  line(base_top_left, top, -e1);

  // Second Side
  line(base_bottom_left, top, -e2);

  // Third Side
  line(base_bottom_right, top, e1);

  // Fourth Side
  line(base_top_right, top, e2);
  glEnd();

  glPopMatrix();
}
