#ifndef OBB_HPP
#define OBB_HPP

#include "bounding_box.hpp"
#include "gl_vec.hpp"

class Physic;
class OBB : public BoundingBox {
  friend Physic;

 protected:
  GLVector<XYZW> local_axis_[3];
  GLVector<XYZ> half_length_;
  const GLVector<XYZ> half_length_orig_;

 public:
  OBB()
      : BoundingBox(nullptr, nullptr)
      , local_axis_{GLVector<XYZW>::XVec,
                    GLVector<XYZW>::YVec,
                    GLVector<XYZW>::ZVec}
      , half_length_()
      , half_length_orig_() {
  }

  OBB(Hitable* h, GLVector<XYZW>* origin, const GLVector<XYZ>& half_length)
      : BoundingBox(h, origin)
      , local_axis_{GLVector<XYZW>::XVec,
                    GLVector<XYZW>::YVec,
                    GLVector<XYZW>::ZVec}
      , half_length_(half_length)
      , half_length_orig_(half_length) {
  }

  OBB(Hitable* h, GLVector<XYZW>* origin, GLVector<XYZ>&& half_length)
      : BoundingBox(h, origin)
      , local_axis_{GLVector<XYZW>::XVec,
                    GLVector<XYZW>::YVec,
                    GLVector<XYZW>::ZVec}
      , half_length_(half_length)
      , half_length_orig_(half_length) {
  }

  virtual ~OBB() {
  }

  void update_rotation(const GLMatrix& xyz) {
    local_axis_[0] = xyz * GLVector<XYZW>::XVec;
    local_axis_[1] = xyz * GLVector<XYZW>::YVec;
    local_axis_[2] = xyz * GLVector<XYZW>::ZVec;
  }

  void update_rotation(const GLVector<XYZ>& rotation) {
    static const double to_rad = 1.0 / 180.0 * M_PI;

    GLMatrix mx;
    mx.set_data(0, 0, 1);
    mx.set_data(1, 1, cos(rotation[0] * to_rad));
    mx.set_data(1, 2, sin(rotation[0] * to_rad));
    mx.set_data(2, 2, mx.get_data(1, 1));
    mx.set_data(2, 1, -mx.get_data(1, 2));
    mx.set_data(3, 3, 1);

    GLMatrix my;
    my.set_data(0, 0, cos(rotation[1] * to_rad));
    my.set_data(0, 2, -sin(rotation[1] * to_rad));
    my.set_data(1, 1, 1);
    my.set_data(2, 0, -my.get_data(0, 2));
    my.set_data(2, 2, my.get_data(0, 0));
    my.set_data(3, 3, 1);

    GLMatrix mz;
    mz.set_data(0, 0, cos(rotation[2] * to_rad));
    mz.set_data(0, 1, sin(rotation[2] * to_rad));
    mz.set_data(1, 0, -mz.get_data(0, 1));
    mz.set_data(1, 1, mz.get_data(0, 0));
    mz.set_data(2, 2, 1);
    mz.set_data(3, 3, 1);

    update_rotation(mz * my * mx);
  }

  void update_scale(const GLVector<XYZ>& scale) {
    half_length_[0] = half_length_orig_[0] * scale[0];
    half_length_[1] = half_length_orig_[1] * scale[1];
    half_length_[2] = half_length_orig_[2] * scale[2];
  }
};
#endif  // ifndef OBB_HPP
