#ifndef HITABLE_HPP
#define HITABLE_HPP

#include <forward_list>
#include <thread>
#include <mutex>
#include <atomic>
#include <unistd.h>

#include "gl_vec.hpp"
#include "bounding_box.hpp"
#include "physic.hpp"
#include "timer.hpp"

class Hitable {
  friend Physic;

  std::atomic<bool> end_;

protected:
  std::forward_list<BoundingBox*> bounding_box_list_;
  std::mutex m_;
  Physic* phy_;
  std::thread* col_t_;

  GLVector<XYZW> speed_;
  double fraction_ = 0.00005;
  bool moveable_;
  bool hitable_;

public:
  Hitable()
      : end_(false)
      , phy_(nullptr)
      , col_t_(nullptr)
      , moveable_(true)
      , hitable_(true) {
  }

  virtual ~Hitable() {
  }

  virtual void step() = 0;

  void start(Physic* phy) {
    if(col_t_ != nullptr) {
      end_ = true;
      col_t_->join();
      delete col_t_;
      col_t_ = nullptr;
      end_ = false;
    }

    phy_ = phy;

    col_t_ = new std::thread([this]() {
      if(phy_ != nullptr) {
        Timer t;
        while(!end_) {
          t.reset();
          step();
          phy_->collision(this);
          usleep(16 - t.elapsed());
        }
      }
    });
  }

  void stop() {
    if(col_t_ != nullptr) {
      end_ = true;
      col_t_->join();
      delete col_t_;
      col_t_ = nullptr;
      end_ = false;
    }
  }

  void add_speed(const GLVector<XYZW>& add) {
    speed_ += add;
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
