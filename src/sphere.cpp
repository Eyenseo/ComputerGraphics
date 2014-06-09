#include "include/sphere.hpp"

Sphere::Sphere() : Drawable(), Hitable() {
}

Sphere::Sphere(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z, 1)
    , Hitable() {
  sb_ = new SphereBB(this, &origin_, .5);
  add_bounding_box(sb_);
}

Sphere::Sphere(double origin_x, double origin_y, double origin_z,
               unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable() {
  sb_ = new SphereBB(this, &origin_, .5);
  add_bounding_box(sb_);
}

Sphere::~Sphere() {
  delete sb_;
}

void Sphere::step() {
   if(moveable_) {
    //TODO review slow speeds are a problem on edges
     speed_ += GLVector<XYZW>::ZVec * -9.81 * 0.0000016 + (speed_ * -fraction_);
     origin_ +=  speed_ * 0.016;
  }
}

void Sphere::draw() {
  const int n1 = 32;
  const int n2 = 32;
  const double a1d = M_PI / n1;
  const double a2d = M_PI / n2;

  set_material_color(1, 0);

  glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0], origin_[1],
              origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  glShadeModel(GL_SMOOTH);
  for(int i = 0; i < n1; ++i) {
    const double a1 = i * a1d;

    // glBegin(GL_LINE_LOOP);
    glBegin(GL_TRIANGLE_STRIP);
    for(int j = 0; j <= n2; ++j) {
      const double a2 = (j + .5 * (i % 2)) * 2 * a2d;
      {
        const double s1 = sin(a1);
        const double c1 = cos(a1);
        const double s2 = sin(a2);
        const double c2 = cos(a2);

        const GLVector<XYZW> normal
            = c1 * GLVector<XYZW>::XVec
              + s1 * (c2 * GLVector<XYZW>::YVec + s2 * GLVector<XYZW>::ZVec);
        glNormal3dv(normal);
        glVertex3dv(0.5 * normal);
      }
      {
        const double s1 = sin(a1 + a1d);
        const double c1 = cos(a1 + a1d);
        const double s2 = sin(a2 + a2d);
        const double c2 = cos(a2 + a2d);

        const GLVector<XYZW> normal
            = c1 * GLVector<XYZW>::XVec
              + s1 * (c2 * GLVector<XYZW>::YVec + s2 * GLVector<XYZW>::ZVec);
        glNormal3dv(normal);
        glVertex3dv(0.5 * normal);
      }
    }
    glEnd();
  }
  glPopMatrix();
}

void Sphere::set_scale(const GLVector<XYZ>& scale) {
  set_scale(scale[0], scale[1], scale[2]);
  sb_->update_scale(scale_);
}

void Sphere::set_scale(double scale) {
  Drawable::set_scale(scale, scale, scale);
  sb_->update_scale(scale_);
}

void Sphere::set_scale(double scale_x, double, double) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_x(double scale_x) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_y(double scale_y) {
  Drawable::set_scale(scale_y, scale_y, scale_y);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_z(double scale_z) {
  Drawable::set_scale(scale_z, scale_z, scale_z);
  sb_->update_scale(scale_);
}
