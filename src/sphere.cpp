#include "include/sphere.hpp"

Sphere::Sphere() : Drawable() {}

Sphere::Sphere(double origin_x, double origin_y, double origin_z, double size
                 = 1) : Drawable(origin_x,
                                 origin_y,
                                 origin_z
                                 ) {
  set_size(size, size, size);
}

Sphere::Sphere(double origin_x, double origin_y, double origin_z, double size_x,
               double size_y, double size_z) : Drawable(origin_x,
                                                        origin_y,
                                                        origin_z)
{
  set_size(size_x, size_y, size_z);
}

Sphere::~Sphere() {}

void Sphere::draw() const {
  Vec3   normal, v1;
  double a1, a1d,
         a2, a2d,
         s1, s2,
         c1, c2;
  int i, j,
      n1 = 64, n2 = 64;

  a1d = M_PI / n1;
  a2d = M_PI / n2;

  SetMaterialColor(1, true);
  SetMaterialColor(2, false);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_.p[0],
              origin_.p[1], origin_.p[2]);

  glShadeModel(GL_SMOOTH);
  for(i = 0; i < n1; i++) {
    a1 = i * a1d;

    glBegin(GL_TRIANGLE_STRIP);
    for(j = 0; j <= n2; j++) {
      a2 = (j + .5 * (i % 2)) * 2 * a2d;

      s1 = sin(a1);
      c1 = cos(a1);
      s2 = sin(a2);
      c2 = cos(a2);

      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1     = boundingbox_[0] / 2 * normal;

      glNormal3dv(normal.p);
      glVertex3dv(v1.p);

      s1 = sin(a1 + a1d);
      c1 = cos(a1 + a1d);
      s2 = sin(a2 + a2d);
      c2 = cos(a2 + a2d);

      normal = c1 * XVec3 + s1 * (c2 * YVec3 + s2 * ZVec3);
      v1     = boundingbox_[0] / 2 * normal;

      glNormal3dv(normal.p);
      glVertex3dv(v1.p);
    }
    glEnd();
  }
  glPopMatrix();
}

void Sphere::set_size(double radius) {
  boundingbox_[0] = radius * 2;
  boundingbox_[1] = radius * 2;
  boundingbox_[2] = radius * 2;
}

void Sphere::set_size(double x, double y, double z) {
  boundingbox_[0] = x * 2;
  boundingbox_[1] = y * 2;
  boundingbox_[2] = z * 2;
}
