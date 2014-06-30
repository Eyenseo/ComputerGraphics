#include <GL/gl.h>
#include <math.h>

#include "include/cylinder.hpp"
#include "include/gl_vec.hpp"

Cylinder::Cylinder()
    : Drawable()
    , Hitable()
    , cb_(nullptr) {
  cb_ = new CylinderBB(this, &origin_, .5, .5);
  add_bounding_box(cb_);
}

Cylinder::Cylinder(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z)
    , Hitable()
    , cb_(nullptr) {
  cb_ = new CylinderBB(this, &origin_, .5, .5);
  add_bounding_box(cb_);
}

Cylinder::Cylinder(double origin_x, double origin_y, double origin_z,
                   unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable()
    , cb_(nullptr) {
  cb_ = new CylinderBB(this, &origin_, .5, .5);
  add_bounding_box(cb_);
}

Cylinder::~Cylinder() {
  delete cb_;
}

void Cylinder::step() {
}

void Cylinder::draw() {
#ifndef M_PI
#define M_PI 3.14159265359
#endif
  auto face = [](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
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
  auto circle = [](const bool top, const int segments) {
    glBegin(GL_TRIANGLE_FAN);
    if(top) {
      glNormal3d(0, 0, 1);
    } else {
      glNormal3d(0, 0, -1);
    }
    glVertex3f(0, 0, (top ? .5 : -.5));
    for(int n = 0; n <= segments; ++n) {
      float const t = 2 * M_PI * (float)n / (float)segments;
      if(top) {
        glNormal3d(0, 0, 1);
      } else {
        glNormal3d(0, 0, -1);
      }
      glVertex3d((top ? cos(t) * .5 : sin(t) * .5),
                 (top ? sin(t) * .5 : cos(t) * .5), (top ? .5 : -.5));
    }
    glEnd();
  };

  set_material_color(1, 0);
  glEnable(GL_NORMALIZE);
  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0], origin_[1],
              origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  // BODY
  const unsigned int segments = 200;
  for(unsigned int n = 0; n <= segments; ++n) {
    const float t0 = 2 * M_PI * (float)n / (float)segments;
    const float t1 = 2 * M_PI * (float)(n + 1) / (float)segments;
    const double a = cos(t0) * .5;
    const double b = sin(t0) * .5;
    const double c = cos(t1) * .5;
    const double d = sin(t1) * .5;
    face(GLVector<XYZW>(a, b, -.5, 1), GLVector<XYZW>(c, d, -.5, 1),
         GLVector<XYZW>(c, d, .5, 1), GLVector<XYZW>(a, b, .5, 1));
  }
  // TOP
  circle(true, segments);
  // BOTTOM
  circle(false, segments);

  glPopMatrix();
}

void Cylinder::set_rotation(const GLVector<XYZ>& rotation) {
  Drawable::set_rotation(rotation);
  cb_->update_rotation(rotation_);
}

void Cylinder::set_rotation(double rotation_x, double rotation_y,
                            double rotation_z) {
  Drawable::set_rotation(rotation_x, rotation_y, rotation_z);
  cb_->update_rotation(rotation_);
}

void Cylinder::set_rotation_x(double rotation) {
  Drawable::set_rotation_x(rotation);
  cb_->update_rotation(rotation_);
}

void Cylinder::set_rotation_y(double rotation) {
  Drawable::set_rotation_y(rotation);
  cb_->update_rotation(rotation_);
}

void Cylinder::set_rotation_z(double rotation) {
  Drawable::set_rotation_z(rotation);
  cb_->update_rotation(rotation_);
}

void Cylinder::set_scale(const GLVector<XYZ>& scale) {
  set_scale(scale[0]);
  cb_->update_scale(scale_);
}

void Cylinder::set_scale(double scale) {
  Drawable::set_scale(scale, scale, scale);
  cb_->update_scale(scale_);
}

void Cylinder::set_scale(double scale_x, double, double scale_z) {
  Drawable::set_scale(scale_x, scale_x, scale_z);
  cb_->update_scale(scale_);
}

void Cylinder::set_scale_x(double scale_x) {
  Drawable::set_scale_x(scale_x);
  Drawable::set_scale_y(scale_x);
  cb_->update_scale(scale_);
}

void Cylinder::set_scale_y(double scale_y) {
  Drawable::set_scale_x(scale_y);
  Drawable::set_scale_y(scale_y);
  cb_->update_scale(scale_);
}

void Cylinder::set_scale_z(double scale_z) {
  Drawable::set_scale_z(scale_z);
  cb_->update_scale(scale_);
}
