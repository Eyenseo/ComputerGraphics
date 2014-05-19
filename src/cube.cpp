#include "include/cube.hpp"

#include <sstream>

Cube::Cube()
  : Drawable(),
  OBB(&(Drawable::origin_)) {}

Cube::Cube(double origin_x, double origin_y, double origin_z)
  : Drawable(origin_x, origin_y, origin_z),
  OBB(&(Drawable::origin_)) {

  local_axis_[0][0] = 1;
  local_axis_[1][1] = 1;
  local_axis_[2][2] = 1;

  half_length_[0] = .5;
  half_length_[1] = .5;
  half_length_[2] = .5;
}

Cube::Cube(double origin_x, double origin_y, double origin_z,
           unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors) ,
  OBB(&(Drawable::origin_)) {}

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


  GLMatrix mv;
  glGetDoublev(GL_MODELVIEW_MATRIX, mv);
  local_axis_[0] = (mv * GLVector<XYZW>::XVec);
  local_axis_[1] = (mv * GLVector<XYZW>::YVec);
  local_axis_[2] = (mv * GLVector<XYZW>::ZVec);


  for(unsigned int i = 0; i < 3; ++i) {
    local_axis_[i][3] = 0;
  }

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
