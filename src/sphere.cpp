#include "include/sphere.hpp"

const GLVector<XYZW> Sphere::XVec(1, 0, 0, 1);
const GLVector<XYZW> Sphere::YVec(0, 1, 0, 1);
const GLVector<XYZW> Sphere::ZVec(0, 0, 1, 1);

Sphere::Sphere()
  : Drawable() {}

Sphere::Sphere(float origin_x, float origin_y, float origin_z)
  : Drawable(origin_x, origin_y, origin_z, 1) {}

Sphere::Sphere(float origin_x, float origin_y, float origin_z,
               unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors)  {}

Sphere::~Sphere() {}

void Sphere::draw() {
  GLVector<XYZW> normal, v1;
  float a1, a1d,
        a2, a2d,
        s1, s2,
        c1, c2;
  int i, j,
      n1 = 32, n2 = 32;

  a1d = M_PI / n1;
  a2d = M_PI / n2;

  set_material_color(1, 0);

  glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0],
              origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  glShadeModel(GL_SMOOTH);
  for(i = 0; i < n1; i++) {
    a1 = i * a1d;

    // glBegin(GL_LINE_LOOP);
    glBegin(GL_TRIANGLE_STRIP);
    for(j = 0; j <= n2; j++) {
      a2 = (j + .5 * (i % 2)) * 2 * a2d;

      s1 = sin(a1);
      c1 = cos(a1);
      s2 = sin(a2);
      c2 = cos(a2);

      normal = c1 * XVec + s1 * (c2 * YVec + s2 * ZVec);
      v1     = 0.5 * normal;

      glNormal3fv(normal);
      glVertex3fv(v1);

      s1 = sin(a1 + a1d);
      c1 = cos(a1 + a1d);
      s2 = sin(a2 + a2d);
      c2 = cos(a2 + a2d);

      normal = c1 * XVec + s1 * (c2 * YVec + s2 * ZVec);
      v1     = 0.5 * normal;

      glNormal3fv(normal.get_vector());
      glVertex3fv(v1.get_vector());
    }
    glEnd();
  }
  glPopMatrix();
}
