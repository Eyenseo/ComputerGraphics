#include "include/table.hpp"

Table::Table()
    : Drawable()
    , Hitable()
    , boxes_origin_{
          // TopLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         0),
          // BottomLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         0),
          // BottomRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         0),
          // TopRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         0),
          // Plank
          GLVector<XYZW>(0, 0, inner_table_height_ + plank_height_ / 2, 0),
          // LeftBorder
          GLVector<XYZW>(-inner_table_length_ / 2 - border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         0),
          // BottomBorder
          GLVector<XYZW>(0,
                         -inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         0),
          // RightBorder
          GLVector<XYZW>(inner_table_length_ / 2 + border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         0),
          // TopBorder
          GLVector<XYZW>(0,
                         +inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         0)}
    , boxes_{// TopLeft Leg
             OBB(this,
                 &boxes_origin_[0],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomLeft Leg
             OBB(this,
                 &boxes_origin_[1],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomRight Leg
             OBB(this,
                 &boxes_origin_[2],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // TopRight Leg
             OBB(this,
                 &boxes_origin_[3],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // Plank
             OBB(this,
                 &boxes_origin_[4],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               inner_table_width_ / 2,
                               plank_height_ / 2)),
             // LeftBorder
             OBB(this,
                 &boxes_origin_[5],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // BottomBorder
             OBB(this,
                 &boxes_origin_[6],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2)),
             // RightBorder
             OBB(this,
                 &boxes_origin_[7],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // TopBorder
             OBB(this,
                 &boxes_origin_[8],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2))} {
  set_color(32, 80, 22, 0);
  set_color(40, 20, 11, 1);
  set_color(7, 9, 24, 2);

  for(unsigned int i = 0; i < 9; ++i) {
    add_bounding_box(&boxes_[i]);
  }
}

Table::Table(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z, 3)
    , Hitable()
    , boxes_origin_{
          // TopLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // BottomLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // BottomRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // TopRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // Plank
          GLVector<XYZW>(0, 0, inner_table_height_ + plank_height_ / 2, 1),
          // LeftBorder
          GLVector<XYZW>(-inner_table_length_ / 2 - border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // BottomBorder
          GLVector<XYZW>(0,
                         -inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // RightBorder
          GLVector<XYZW>(inner_table_length_ / 2 + border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // TopBorder
          GLVector<XYZW>(0,
                         +inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         1)}
    , boxes_{// TopLeft Leg
             OBB(this,
                 &boxes_origin_[0],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomLeft Leg
             OBB(this,
                 &boxes_origin_[1],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomRight Leg
             OBB(this,
                 &boxes_origin_[2],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // TopRight Leg
             OBB(this,
                 &boxes_origin_[3],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // Plank
             OBB(this,
                 &boxes_origin_[4],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               inner_table_width_ / 2,
                               plank_height_ / 2)),
             // LeftBorder
             OBB(this,
                 &boxes_origin_[5],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // BottomBorder
             OBB(this,
                 &boxes_origin_[6],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2)),
             // RightBorder
             OBB(this,
                 &boxes_origin_[7],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // TopBorder
             OBB(this,
                 &boxes_origin_[8],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2))} {
  set_color(32, 80, 22, 0);
  set_color(40, 20, 11, 1);
  set_color(7, 9, 24, 2);

  for(unsigned int i = 0; i < 9; ++i) {
    add_bounding_box(&boxes_[i]);
  }
}

Table::Table(double origin_x,
             double origin_y,
             double origin_z,
             unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable()
    , boxes_origin_{
          // TopLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // BottomLeft Leg
          GLVector<XYZW>(-inner_table_length_ / 2 + border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // BottomRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         -inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // TopRight Leg
          GLVector<XYZW>(inner_table_length_ / 2 - border_width_ / 2,
                         inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ / 2,
                         1),
          // Plank
          GLVector<XYZW>(0, 0, inner_table_height_ + plank_height_ / 2, 1),
          // LeftBorder
          GLVector<XYZW>(-inner_table_length_ / 2 - border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // BottomBorder
          GLVector<XYZW>(0,
                         -inner_table_width_ / 2 - border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // RightBorder
          GLVector<XYZW>(inner_table_length_ / 2 + border_width_ / 2,
                         0,
                         inner_table_height_ + border_height_ / 2,
                         1),
          // TopBorder
          GLVector<XYZW>(0,
                         +inner_table_width_ / 2 + border_width_ / 2,
                         inner_table_height_ + border_height_ / 2,
                         1)}
    , boxes_{// TopLeft Leg
             OBB(this,
                 &boxes_origin_[0],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomLeft Leg
             OBB(this,
                 &boxes_origin_[1],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // BottomRight Leg
             OBB(this,
                 &boxes_origin_[2],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // TopRight Leg
             OBB(this,
                 &boxes_origin_[3],
                 GLVector<XYZ>(border_width_ / 2,
                               border_width_ / 2,
                               inner_table_height_ / 2)),
             // Plank
             OBB(this,
                 &boxes_origin_[4],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               inner_table_width_ / 2,
                               plank_height_ / 2)),
             // LeftBorder
             OBB(this,
                 &boxes_origin_[5],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // BottomBorder
             OBB(this,
                 &boxes_origin_[6],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2)),
             // RightBorder
             OBB(this,
                 &boxes_origin_[7],
                 GLVector<XYZ>(border_width_ / 2,
                               inner_table_width_ / 2,
                               border_height_ / 2)),
             // TopBorder
             OBB(this,
                 &boxes_origin_[8],
                 GLVector<XYZ>(inner_table_length_ / 2,
                               border_width_ / 2,
                               border_height_ / 2))} {
  set_color(32, 80, 22, 0);
  set_color(40, 20, 11, 1);
  set_color(7, 9, 24, 2);

  for(unsigned int i = 0; i < 9; ++i) {
    add_bounding_box(&boxes_[i]);
  }
}

Table::~Table() {
}

void Table::step() {
}

void Table::draw() {
  GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

  // glEnable(GL_RESCALE_NORMAL); // TODO Needed?
  rotate_from(rotation_[0], rotation_[1], rotation_[2],
              origin_[0], origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  GLMatrix mv;
  glGetDoublev(GL_MODELVIEW_MATRIX, mv);
 /* local_axis_[0] = (mv * GLVector<XYZW>::XVec);
  local_axis_[1] = (mv * GLVector<XYZW>::YVec);
  local_axis_[2] = (mv * GLVector<XYZW>::ZVec);
*/
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

void Table::set_rotation(const GLVector<XYZ>& rotation) {
  Drawable::set_rotation(rotation);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_rotation(rotation_);
  }
}

void Table::set_rotation(double rotation_x, double rotation_y,
                         double rotation_z) {
  Drawable::set_rotation(rotation_x, rotation_y, rotation_z);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_rotation(rotation_);
  }
}

void Table::set_rotation_x(double rotation) {
  Drawable::set_rotation_x(rotation);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_rotation(rotation_);
  }
}

void Table::set_rotation_y(double rotation) {
  Drawable::set_rotation_y(rotation);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_rotation(rotation_);
  }
}

void Table::set_rotation_z(double rotation) {
  Drawable::set_rotation_z(rotation);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_rotation(rotation_);
  }
}

void Table::set_scale(const GLVector<XYZ>& scale) {
  Drawable::set_scale(scale);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}

void Table::set_scale(double scale) {
  Drawable::set_scale(scale);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}

void Table::set_scale(double scale_x, double scale_y, double scale_z) {
  Drawable::set_scale(scale_x, scale_y, scale_z);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}

void Table::set_scale_x(double scale_x) {
  Drawable::set_scale_x(scale_x);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}

void Table::set_scale_y(double scale_y) {
  Drawable::set_scale_y(scale_y);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}

void Table::set_scale_z(double scale_z) {
  Drawable::set_scale_z(scale_z);

  for(unsigned int i = 0; i < 9; ++i) {
    boxes_[i].update_scale(scale_);
  }
}
