#ifndef HITABLE_HPP
#define HITABLE_HPP

#include <forward_list>

#include "gl_vec.hpp"
#include "bounding_box.hpp"

class Physic;
class Hitable {
  friend Physic;

 protected:
  std::forward_list<BoundingBox*> bounding_box_list;
  GLVector<XYZW> speed_;
  double fraction_ = 0.005;
  bool moveable_;

 public:
  Hitable()
      : moveable_(true) {
  }

  virtual ~Hitable() {
  }

  virtual void step() = 0;

  void add_speed(const GLVector<XYZW>& add) {
    speed_ += add;
  }

  void add_bounding_box(BoundingBox* bb) {
    bounding_box_list.push_front(bb);
  }

  void remove_bounduing_box(BoundingBox* bb) {
    bounding_box_list.remove(bb);
  }

  void set_moveable(bool moveable) {
    moveable_ = moveable;
  }

  bool is_moveable() {
    return moveable_;
  }
};
#endif  // ifndef HITABLE_HPP
