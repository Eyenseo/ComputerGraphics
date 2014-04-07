#include "include/cube.hpp"

#include <sstream>

Cube::Cube()
  : Drawable() {}

Cube::Cube(float origin_x, float origin_y, float origin_z)
  : Drawable(origin_x, origin_y, origin_z) {}

Cube::Cube(float origin_x, float origin_y, float origin_z, unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors)  {}

Cube::~Cube() {}

void Cube::draw() {
  GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

  auto face
    = [&](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
          const GLVector<XYZW>& v3, const GLVector<XYZW>& v4) {
        GLVector<XYZ> normal = (v2 - v1) % (v3 - v1);

        glBegin(GL_QUADS);
        normal.Normalize();
        glNormal3fv(normal);
        glVertex3fv(v1);
        glVertex3fv(v2);
        glVertex3fv(v3);
        glVertex3fv(v4);
        glEnd();
      };

  // faces_->clear();

  set_material_color(1, 0);

  // glEnable(GL_RESCALE_NORMAL); // TODO Needed?
  glMatrixMode(GL_MODELVIEW);
  rotate_from(rotation_[0], rotation_[1], rotation_[2],
              origin_[0], origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  glGetFloatv(GL_MODELVIEW_MATRIX, model_view);
  // auto mat_out = [&]() -> std::string {
  // std::ostringstream ss;

  // for(unsigned int m = 0; m < 4; m++) {
  // for(int n = 0; n < 4; n++) {
  // ss << model_view[m + n * 4] << '\t' << '\t';
  // }
  // ss << '\n';
  // }
  // return ss.str();
  // };

  // std::cout << mat_out() << std::endl;

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
