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

  GLVector<XYZW> speed_;
  double fraction_ = 0.0035;
  bool moveable_;
  bool hitable_;

public:
  Hitable()
      : moveable_(true)
      , hitable_(true) {
  }

  virtual ~Hitable() {
  }

  virtual void step() = 0;

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
};
#endif  // ifndef HITABLE_HPP
