#include "include/animated_cube.hpp"

#include <functional>

AnimatedCube::AnimatedCube()
  : Cube(),
  state_(CLOSED),
  open_angel_(120),
  closed_angel_(0),
  current_angle_(0),
  animation_time_(0) {}

AnimatedCube::AnimatedCube(double origin_x, double origin_y, double origin_z)
  : Cube(origin_x, origin_y, origin_z),
  state_(CLOSED),
  open_angel_(120),
  closed_angel_(0),
  current_angle_(0),
  animation_time_(0) {}

AnimatedCube::AnimatedCube(double origin_x, double origin_y, double origin_z,
                           unsigned char colors)
  : Cube(origin_x, origin_y, origin_z, colors),
  state_(CLOSED),
  open_angel_(120),
  closed_angel_(0),
  current_angle_(0),
  animation_time_(0) {}

AnimatedCube::~AnimatedCube() {}

/**
 * Calculates the new angel of the lid of the box
 */
void AnimatedCube::calculate_current_angle() {
  if(((state_ == OPENING) && (state_ != OPEN))
     || ((state_ == CLOSING) && (state_ != CLOSED))) {
    std::function<double()> fun // logistic function for the opening and closing of the lid
      = [&]() -> double {
          return open_angel_
                 * 1 / (1
                        + pow(M_E, -0.0011 * open_angel_ * animation_time_)
                        * (open_angel_ / .5 - 1));
        };

    if(state_ == OPENING) {
      animation_time_ += 0.25;
      current_angle_   = fun();

      if(current_angle_ >= open_angel_ - .1) {
        current_angle_ = open_angel_;
        state_ = OPEN;
      }
    } else {
      animation_time_ -= 0.25;
      current_angle_   = fun();

      if(current_angle_ <= closed_angel_ + .1) {
        current_angle_ = closed_angel_;
        state_ = CLOSED;
      }
    }
  }
}

void AnimatedCube::draw() {
  GLVector<XYZW> bottom_left  = GLVector<XYZW>(-.5, -.5, 0, 1);
  GLVector<XYZW> top_left     = GLVector<XYZW>(-.5, .5, 0, 1);
  GLVector<XYZW> top_right    = GLVector<XYZW>(.5, .5, 0, 1);
  GLVector<XYZW> bottom_right = GLVector<XYZW>(.5, -.5, 0, 1);

  auto face
    = [this](const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
             const GLVector<XYZW>& v3, const GLVector<XYZW>& v4) {
        GLVector<XYZ> normal = (v2 - v1) % (v3 - v1);

        glBegin(GL_QUADS);
        glNormal3dv(normal);
        glVertex3dv(v1);
        glVertex3dv(v2);
        glVertex3dv(v3);
        glVertex3dv(v4);
        glEnd();
      };

  calculate_current_angle();

  set_material_color(1, 0);
  set_material_color(2, 1);

  // glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2],
              origin_[0], origin_[1], origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);

  // Bottom
  rotate_from(0, 0, 0, 0, 0, -.5);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Top
  glPopMatrix();
  rotate_from(180,             0, 0, 0,  0,  .5); // move up and flip
  rotate_from(-current_angle_, 0, 0, 0,  -.5, 0); // move to the back and rotate
  rotate_from(0,               0, 0, 0, .5,   0); // move back to centre
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

  // Front
  glPopMatrix();
  rotate_from(90, 180, 0, 0, -.5, 0);
  face(top_left, top_right, bottom_right, bottom_left);

  glPopMatrix();
  glPopMatrix();
}

void AnimatedCube::open() {
  state_ = OPENING;
}

void AnimatedCube::close() {
  state_ = CLOSING;
}
