#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <chrono>

class Timer {
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::duration<double, std::ratio<60, 1>> MS;
  std::chrono::time_point<Clock> beg_;

public:
  Timer()
      : beg_(Clock::now()) {
  }

  void reset() {
    beg_ = Clock::now();
  }

  double elapsed() const {
    return std::chrono::duration_cast<MS>(Clock::now() - beg_).count();
  }
};
#endif
