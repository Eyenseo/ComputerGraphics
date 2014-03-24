#include "include/animated_cube.hpp"

AnimatedCube::AnimatedCube()
  : Cube(),
  state_(CLOSED),
  open_angel_(120),
  closed_angel_(0),
  current_angle_(0),
  animation_time_(0) {}

AnimatedCube::AnimatedCube(double origin_x, double origin_y, double origin_z,
                           double size = 1)
  : Cube(origin_x, origin_y, origin_z, size),
  state_(CLOSED),
  open_angel_(120),
  closed_angel_(0),
  current_angle_(0),
  animation_time_(0) {}

AnimatedCube::AnimatedCube(double origin_x, double origin_y, double origin_z,
                           double size_x, double size_y, double size_z)
  : Cube(origin_x, origin_y, origin_z, size_x, size_y, size_z),
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
    std::function<float()> fun // logistic function for the opening and closing of the lid
      = [&]() -> float {
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
  double half_length = .5 * boundingbox_[0];

  Vec3 bottom_left  = Vec3(-half_length, -half_length, 0);
  Vec3 top_left     = Vec3(-half_length, half_length, 0);
  Vec3 top_right    = Vec3(half_length, half_length, 0);
  Vec3 bottom_right = Vec3(half_length, -half_length, 0);

  auto face
    = [this](const Vec3& v1, const Vec3& v2, const Vec3& v3, const Vec3& v4) {
        Vec3 normal = (v2 - v1) % (v3 - v1);

        normal.Normalize();

        glNormal3dv(normal.p);
        glVertex3dv(v1.p);
        glVertex3dv(v2.p);
        glVertex3dv(v3.p);
        glVertex3dv(v4.p);
      };

  calculate_current_angle();

  SetMaterialColor(1, true);
  SetMaterialColor(2, false);

  glEnable(GL_RESCALE_NORMAL);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_.p[0],
              origin_.p[1], origin_.p[2]);
  glScalef(scale_, scale_, scale_);

  // Bottom
  rotate_from(0, 0, 0, 0, 0, -half_length);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Top
  glPopMatrix();
  rotate_from(180,             0, 0, 0,           0,  half_length); // move up and flip
  rotate_from(-current_angle_, 0, 0, 0,           -half_length, 0); // move to the back and rotate
  rotate_from(0,               0, 0, 0, half_length,            0); // move back to centre
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Left
  glPopMatrix();
  glPopMatrix();
  glPopMatrix();
  rotate_from(0, 90, 0, -half_length, 0, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Back
  glPopMatrix();
  rotate_from(90, 0, 0, 0, half_length, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Right
  glPopMatrix();
  rotate_from(0, 270, 0, half_length, 0, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  // Front
  glPopMatrix();
  rotate_from(90, 180, 0, 0, -half_length, 0);
  glBegin(GL_QUADS);
  face(top_left, top_right, bottom_right, bottom_left);
  glEnd();

  glPopMatrix();
  glPopMatrix();
}

void AnimatedCube::set_size(double size) {
  boundingbox_[0] = size;
  boundingbox_[1] = size;
  boundingbox_[2] = size;
}

void AnimatedCube::set_size(double x, double y, double z) {
  boundingbox_[0] = x;
  boundingbox_[1] = y;
  boundingbox_[2] = z;
}

/**
 * The function will return a function that can handle a key event.
 * The returned function will enable the opening sequence of the cube lid
 * @param  trigger number that represents the key pressed
 * @return         function that will start the opening sequence of the cube lid
 */
std::function<void(int,
                   int)>AnimatedCube::open_key_callback(const int trigger) {
  std::function<void(int event, int action)> callback
    = [this, trigger](int event, int action) {
        if((trigger == event) && (action == 1)) {
          state_ = OPENING;
        }
      };

  return callback;
}

/**
 * The function will return a function that can handle a key event.
 * The returned function will enable the closing sequence of the cube lid
 * @param  trigger number that represents the key pressed
 * @return         function that will start the closing sequence of the cube lid
 */
std::function<void(int,
                   int)>AnimatedCube::close_key_callback(const int trigger) {
  std::function<void(int event, int action)> callback
    = [this, trigger](int event, int action) {
        if((trigger == event) && (action == 1)) {
          state_ = CLOSING;
        }
      };

  return callback;
}
