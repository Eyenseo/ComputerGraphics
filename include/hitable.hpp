#ifndef HITABLE_HPP
#define HITABLE_HPP

#include <forward_list>

#include "gl_vec.hpp"
#include "bounding_box.hpp"
#include "physic.hpp"

class Hitable {
  friend Physic;

protected:
  std::forward_list<BoundingBox*> bounding_box_list_;

  std::function<void(const Hitable*)> on_collision_;
  GLVector<XYZW> speed_;
  float fraction_;
  bool only_test;
  bool hitable_;
  bool moveable_;

public:
  Hitable()
      : on_collision_([](const Hitable*) {})
      , speed_(0, 0, 0, 0)
      , fraction_(0.0035)
      , only_test(false)
      , hitable_(true)
      , moveable_(true) {
  }

  virtual ~Hitable() {
  }

  virtual void step() = 0;

  void on_collision(Hitable* h) {
    on_collision_(h);
  }

  void set_on_collision(std::function<void(const Hitable*)> f) {
    on_collision_ = f;
  }

  float get_fraction() {
    return fraction_;
  }

  void set_fraction(float fraction) {
    fraction_ = fraction;
  }

  void add_speed(const GLVector<XYZW>& add) {
    speed_ += add;
  }

  void set_speed(const GLVector<XYZW>& speed) {
    speed_ = speed;
  }

  GLVector<XYZW> get_speed() {
    return speed_;
  }

  void add_bounding_box(BoundingBox* bb) {
    bounding_box_list_.push_front(bb);
  }

  void remove_bounduing_box(BoundingBox* bb) {
    bounding_box_list_.remove(bb);
  }

  void set_moveable(bool moveable) {
    moveable_ = moveable;
  }

  bool is_moveable() const {
    return moveable_;
  }

  void set_hitable(bool hitable) {
    hitable_ = hitable;
  }

  bool is_hitable() const {
    return hitable_;
  }

  void set_only_test(bool test) {
    only_test = test;
  }

  bool is_only_test() const {
    return only_test;
  }
};
#endif  // ifndef HITABLE_HPP
