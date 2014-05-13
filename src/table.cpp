#include "include/table.hpp"

Table::Table()
  : Drawable() {}

Table::Table(double origin_x, double origin_y, double origin_z)
  : Drawable(origin_x, origin_y, origin_z, 3) {
  set_color(32, 80, 22, 0);
  set_color(40, 20, 11, 1);
  set_color( 7,  9, 24, 2);
}

Table::Table(double origin_x, double origin_y, double origin_z,
             unsigned char colors)
  : Drawable(origin_x, origin_y, origin_z, colors)  {}

Table::~Table() {}

void Table::draw() {
  GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

  // glEnable(GL_RESCALE_NORMAL); // TODO Needed?
  rotate_from(rotation_[0], rotation_[1], rotation_[2],
              origin_[0], origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  set_material_color(1, 1);
  short_border();
  long_border();
  plank();
  set_material_color(1, 2);
  legs();
  glPopMatrix();
}

void Table::face(const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
                 const GLVector<XYZW>& v3, const GLVector<XYZW>& v4) {
  GLVector<XYZ> normal = (v2 - v1) % (v3 - v1);

  // glBegin(GL_LINE_STRIP);
  glBegin(GL_QUADS);
  normal.Normalize();
  glNormal3dv(normal);
  glVertex3dv(v1);
  glVertex3dv(v2);
  glVertex3dv(v3);
  glVertex3dv(v4);
  glEnd();
}

/**
 *                    Outer
 *                     Top
 *        |--------------------------|
 *        |           Inner          |
 *        |            Top           |
 *  Outer | Inner             Inner  | Outer
 *  Left  | Left      Inner   Right  | Right
 *        |           Bottom         |
 *        |--------------------------|
 *                    Outer
 *                    Bottom
 */
void Table::short_border() {
  // Left - top
  GLVector<XYZW> top_left
    = GLVector<XYZW>(-inner_table_length_ / 2 - border_width_,
                     inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_left
    = GLVector<XYZW>(-inner_table_length_ / 2 - border_width_,
                     -inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_right
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     -inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> top_right
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  face(top_left, bottom_left, bottom_right, top_right);

  // Left - outer
  top_left[1]     = inner_table_width_ / 2 + border_width_;
  top_left[2]     = inner_table_height_;
  bottom_left[2]  = inner_table_height_;
  bottom_left[1]  = -inner_table_width_ / 2 - border_width_;
  bottom_right[0] = -inner_table_length_ / 2 - border_width_;
  bottom_right[1] = -inner_table_width_ / 2 - border_width_;
  top_right[0]    = -inner_table_length_ / 2 - border_width_;
  top_right[1]    = inner_table_width_ / 2 + border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Left - inner
  top_left[0]     = -inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2;
  top_left[2]     = inner_table_height_ + border_height_ + plank_height_;
  bottom_left[0]  = -inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2;
  bottom_left[2]  = inner_table_height_ + border_height_ + plank_height_;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2;
  bottom_right[2] = inner_table_height_ + plank_height_;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2;
  top_right[2]    = inner_table_height_ + plank_height_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Right - top
  top_left[0]     = inner_table_length_ / 2;
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_right[0] = inner_table_length_ / 2 + border_width_;
  bottom_right[2] = inner_table_height_ + border_height_ + plank_height_;
  top_right[0]    = inner_table_length_ / 2 + border_width_;
  top_right[2]    = inner_table_height_ + border_height_ + plank_height_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Right - outer
  top_left[0]     = inner_table_length_ / 2 + border_width_;
  top_left[1]     = inner_table_width_ / 2 + border_width_;
  bottom_left[1]  = -inner_table_width_ / 2 - border_width_;
  bottom_left[0]  = inner_table_length_ / 2 + border_width_;
  bottom_right[1] = -inner_table_width_ / 2 - border_width_;
  bottom_right[2] = inner_table_height_;
  top_right[1]    = inner_table_width_ / 2 + border_width_;
  top_right[2]    = inner_table_height_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Right - inner
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2;
  top_left[2]     = inner_table_height_ + plank_height_;
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2;
  bottom_left[2]  = inner_table_height_ + plank_height_;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2;
  bottom_right[2] = inner_table_height_ + border_height_ + plank_height_;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2;
  top_right[2]    = inner_table_height_ + border_height_ + plank_height_;
  face(top_left, bottom_left, bottom_right, top_right);
}

/**
 *                    Outer
 *                     Top
 *        |--------------------------|
 *        |           Inner          |
 *        |            Top           |
 *  Outer | Inner             Inner  | Outer
 *  Left  | Left      Inner   Right  | Right
 *        |           Bottom         |
 *        |--------------------------|
 *                    Outer
 *                    Bottom
 */
void Table::long_border() {
  // Top - top
  GLVector<XYZW> top_left
    = GLVector<XYZW>(-inner_table_length_ / 2 - border_width_,
                     inner_table_width_ / 2 + border_width_,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_left
    = GLVector<XYZW>(-inner_table_length_ / 2 - border_width_,
                     inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_right
    = GLVector<XYZW>(inner_table_length_ / 2 + border_width_,
                     inner_table_width_ / 2,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  GLVector<XYZW> top_right
    = GLVector<XYZW>(inner_table_length_ / 2 + border_width_,
                     inner_table_width_ / 2 + border_width_,
                     inner_table_height_ + border_height_ + plank_height_,
                     1);
  face(top_left, bottom_left, bottom_right, top_right);

  // Top - outer
  top_left[2]     = inner_table_height_;
  bottom_left[1]  = inner_table_width_ / 2 + border_width_;
  bottom_right[1] = inner_table_width_ / 2 + border_width_;
  top_right[2]    = inner_table_height_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Top - inner
  top_left[0]     = -inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2;
  top_left[2]     = inner_table_height_ + plank_height_;
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = inner_table_width_ / 2;
  bottom_left[2]  = inner_table_height_ + plank_height_;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = inner_table_width_ / 2;
  bottom_right[2] = inner_table_height_ + border_height_ + plank_height_;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2;
  top_right[2]    = inner_table_height_ + border_height_ + plank_height_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom - top
  top_left[0]     = -inner_table_length_ / 2 - border_width_;
  top_left[1]     = -inner_table_width_ / 2;
  top_left[2]     = inner_table_height_ + border_height_ + plank_height_;
  bottom_left[0]  = -inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = -inner_table_width_ / 2 - border_width_;
  bottom_left[2]  = inner_table_height_ + border_height_ + plank_height_;
  bottom_right[0] = inner_table_length_ / 2 + border_width_;
  bottom_right[1] = -inner_table_width_ / 2 - border_width_;
  top_right[0]    = inner_table_length_ / 2 + border_width_;
  top_right[1]    = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom - outer
  top_left[1]     = -inner_table_width_ / 2 - border_width_;
  bottom_left[2]  = inner_table_height_;
  bottom_right[2] = inner_table_height_;
  top_right[1]    = -inner_table_width_ / 2 - border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom - inner
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = -inner_table_width_ / 2;
  top_left[2]     = inner_table_height_ + plank_height_;
  bottom_left[0]  = -inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2;
  bottom_left[2]  = inner_table_height_ + plank_height_;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2;
  bottom_right[2] = inner_table_height_ + border_height_ + plank_height_;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = -inner_table_width_ / 2;
  top_right[2]    = inner_table_height_ + border_height_ + plank_height_;
  face(top_left, bottom_left, bottom_right, top_right);
}

/**
 *                    Outer
 *                     Top
 *        |--------------------------|
 *        |           Inner          |
 *        |            Top           |
 *  Outer | Inner             Inner  | Outer
 *  Left  | Left      Inner   Right  | Right
 *        |           Bottom         |
 *        |--------------------------|
 *                    Outer
 *                    Bottom
 */
void Table::plank() {
  // Top
  set_material_color(1, 0);
  GLVector<XYZW> top_left
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     inner_table_width_ / 2,
                     inner_table_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_left
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     -inner_table_width_ / 2,
                     inner_table_height_ + plank_height_,
                     1);
  GLVector<XYZW> bottom_right
    = GLVector<XYZW>(inner_table_length_ / 2,
                     -inner_table_width_ / 2,
                     inner_table_height_ + plank_height_,
                     1);
  GLVector<XYZW> top_right
    = GLVector<XYZW>(inner_table_length_ / 2,
                     inner_table_width_ / 2,
                     inner_table_height_ + plank_height_,
                     1);
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom
  set_material_color(1, 1);
  top_left[0]     = -inner_table_length_ / 2 - border_width_;
  top_left[1]     = -inner_table_width_ / 2 - border_width_;
  top_left[2]     = inner_table_height_;
  bottom_left[0]  = -inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = inner_table_width_ / 2 + border_width_;
  bottom_left[2]  = inner_table_height_;
  bottom_right[0] = inner_table_length_ / 2 + border_width_;
  bottom_right[1] = inner_table_width_ / 2 + border_width_;
  bottom_right[2] = inner_table_height_;
  top_right[0]    = inner_table_length_ / 2 + border_width_;
  top_right[1]    = -inner_table_width_ / 2 - border_width_;
  top_right[2]    = inner_table_height_;
  face(top_left, bottom_left, bottom_right, top_right);
}

void Table::legs() {
  // TopLeft
  // TopLeft - ground
  GLVector<XYZW> top_left
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     inner_table_width_ / 2 - border_width_,
                     0,
                     1);
  GLVector<XYZW> bottom_left
    = GLVector<XYZW>(-inner_table_length_ / 2,
                     inner_table_width_ / 2,
                     0,
                     1);
  GLVector<XYZW> bottom_right
    = GLVector<XYZW>(-inner_table_length_ / 2 + border_width_,
                     inner_table_width_ / 2,
                     0,
                     1);
  GLVector<XYZW> top_right
    = GLVector<XYZW>(-inner_table_length_ / 2 + border_width_,
                     inner_table_width_ / 2 - border_width_,
                     0,
                     1);
  face(top_left, bottom_left, bottom_right, top_right);

  // TopLeft - left
  top_left[2]     = inner_table_height_;
  bottom_left[2]  = inner_table_height_;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = inner_table_width_ / 2;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2 - border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopLeft - bottom
  top_left[0]     = -inner_table_length_ / 2 + border_width_;
  top_left[1]     = inner_table_width_ / 2 - border_width_;
  bottom_left[0]  = -inner_table_length_ / 2;
  bottom_left[1]  = inner_table_width_ / 2 - border_width_;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = inner_table_width_ / 2 - border_width_;
  top_right[0]    = -inner_table_length_ / 2 + border_width_;
  top_right[1]    = inner_table_width_ / 2 - border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopLeft - right
  top_left[0]     = -inner_table_length_ / 2 + border_width_;
  top_left[1]     = inner_table_width_ / 2;
  bottom_left[0]  = -inner_table_length_ / 2 + border_width_;
  bottom_left[1]  = inner_table_width_ / 2 - border_width_;
  bottom_right[0] = -inner_table_length_ / 2 + border_width_;
  bottom_right[1] = inner_table_width_ / 2 - border_width_;
  top_right[0]    = -inner_table_length_ / 2 + border_width_;
  top_right[1]    = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopLeft - top
  top_left[0]     = -inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2;
  bottom_left[0]  = -inner_table_length_ / 2 + border_width_;
  bottom_left[1]  = inner_table_width_ / 2;
  bottom_right[0] = -inner_table_length_ / 2 + border_width_;
  bottom_right[1] = inner_table_width_ / 2;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom Left
  // BottomLeft - ground
  top_left[0]     = -inner_table_length_ / 2;
  top_left[1]     = -inner_table_width_ / 2;
  top_left[2]     = 0;
  bottom_left[0]  = -inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2 + border_width_;
  bottom_left[2]  = 0;
  bottom_right[0] = -inner_table_length_ / 2 + border_width_;
  bottom_right[1] = -inner_table_width_ / 2 + border_width_;
  top_right[0]    = -inner_table_length_ / 2 + border_width_;
  top_right[1]    = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomLeft - left
  top_left[2]     = inner_table_height_;
  bottom_left[2]  = inner_table_height_;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2 + border_width_;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomLeft - bottom
  top_left[0]     = -inner_table_length_ / 2;
  top_left[1]     = -inner_table_width_ / 2 + border_width_;
  bottom_left[0]  = -inner_table_length_ / 2 + border_width_;
  bottom_left[1]  = -inner_table_width_ / 2 + border_width_;
  top_right[0]    = -inner_table_length_ / 2;
  top_right[1]    = -inner_table_width_ / 2 + border_width_;
  bottom_right[0] = -inner_table_length_ / 2 + border_width_;
  bottom_right[1] = -inner_table_width_ / 2 + border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomLeft - right
  top_left[0]     = -inner_table_length_ / 2 + border_width_;
  top_left[1]     = -inner_table_width_ / 2 + border_width_;
  bottom_left[0]  = -inner_table_length_ / 2 + border_width_;
  bottom_left[1]  = -inner_table_width_ / 2;
  top_right[0]    = -inner_table_length_ / 2 + border_width_;
  top_right[1]    = -inner_table_width_ / 2 + border_width_;
  bottom_right[0] = -inner_table_length_ / 2 + border_width_;
  bottom_right[1] = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomLeft - top
  top_left[0]     = -inner_table_length_ / 2 + border_width_;
  top_left[1]     = -inner_table_width_ / 2;
  bottom_left[0]  = -inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2;
  top_right[0]    = -inner_table_length_ / 2 + border_width_;
  top_right[1]    = -inner_table_width_ / 2;
  bottom_right[0] = -inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // Bottom Right
  // BottomRight - ground
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2;
  bottom_left[2]  = 0;
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = -inner_table_width_ / 2 + border_width_;
  top_left[2]     = 0;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = -inner_table_width_ / 2 + border_width_;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomRight - left
  bottom_left[2]  = inner_table_height_;
  top_left[2]     = inner_table_height_;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = -inner_table_width_ / 2 + border_width_;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomRight - bottom
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = -inner_table_width_ / 2 + border_width_;
  top_left[0]     = inner_table_length_ / 2 - border_width_;
  top_left[1]     = -inner_table_width_ / 2 + border_width_;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = -inner_table_width_ / 2 + border_width_;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = -inner_table_width_ / 2 + border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomRight - right
  bottom_left[0]  = inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = -inner_table_width_ / 2 + border_width_;
  top_left[0]     = inner_table_length_ / 2 - border_width_;
  top_left[1]     = -inner_table_width_ / 2;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = -inner_table_width_ / 2 + border_width_;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // BottomRight - top
  bottom_left[0]  = inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = -inner_table_width_ / 2;
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = -inner_table_width_ / 2;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = -inner_table_width_ / 2;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = -inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // Top Right
  // TopRight - ground
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2;
  top_left[2]     = 0;
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = inner_table_width_ / 2 - border_width_;
  bottom_left[2]  = 0;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = inner_table_width_ / 2 - border_width_;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopRight - left
  top_left[2]     = inner_table_height_;
  bottom_left[2]  = inner_table_height_;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = inner_table_width_ / 2 - border_width_;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopRight - bottom
  top_left[0]     = inner_table_length_ / 2;
  top_left[1]     = inner_table_width_ / 2 - border_width_;
  bottom_left[0]  = inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = inner_table_width_ / 2 - border_width_;
  top_right[0]    = inner_table_length_ / 2;
  top_right[1]    = inner_table_width_ / 2 - border_width_;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = inner_table_width_ / 2 - border_width_;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopRight - right
  top_left[0]     = inner_table_length_ / 2 - border_width_;
  top_left[1]     = inner_table_width_ / 2 - border_width_;
  bottom_left[0]  = inner_table_length_ / 2 - border_width_;
  bottom_left[1]  = inner_table_width_ / 2;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = inner_table_width_ / 2 - border_width_;
  bottom_right[0] = inner_table_length_ / 2 - border_width_;
  bottom_right[1] = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);

  // TopRight - top
  top_left[0]     = inner_table_length_ / 2 - border_width_;
  top_left[1]     = inner_table_width_ / 2;
  bottom_left[0]  = inner_table_length_ / 2;
  bottom_left[1]  = inner_table_width_ / 2;
  top_right[0]    = inner_table_length_ / 2 - border_width_;
  top_right[1]    = inner_table_width_ / 2;
  bottom_right[0] = inner_table_length_ / 2;
  bottom_right[1] = inner_table_width_ / 2;
  face(top_left, bottom_left, bottom_right, top_right);
}
