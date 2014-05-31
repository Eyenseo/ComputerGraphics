#ifndef TABLE_HPP
#define TABLE_HPP value

#include "drawable.hpp"
#include "hitable.hpp"
#include "obb.hpp"

class Table : public Drawable , public Hitable {
  const double inner_table_height_ = 5;
  const double inner_table_length_ = 14;
  const double inner_table_width_  = 10;

  const double plank_height_ = 0.1;

  const double border_height_ = 0.7;
  const double border_width_  = 0.5;

  void short_border();
  void long_border();
  void plank();
  void legs();
  void face(const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
            const GLVector<XYZW>& v3, const GLVector<XYZW>& v4);

protected:

  GLVector<XYZW>& origin_ = Drawable::origin_;

  GLVector<XYZW> boxes_origin_[9];
  OBB boxes_[9];

public:

  Table();
  Table(double origin_x, double origin_y, double origin_z);
  Table(double origin_x, double origin_y, double origin_z,
        unsigned char colors);
  ~Table();

  virtual void draw();
  virtual void step();

  virtual void set_rotation(const GLVector<XYZ>& rotation);
  virtual void set_rotation(double rotation_x,
                            double rotation_y,
                            double rotation_z);
  virtual void set_rotation_x(double rotation);
  virtual void set_rotation_y(double rotation);
  virtual void set_rotation_z(double rotation);

  virtual void set_scale(const GLVector<XYZ>& scale);
  virtual void set_scale(double scale);
  virtual void set_scale(double scale_x, double scale_y, double scale_z);
  virtual void set_scale_x(double scale_x);
  virtual void set_scale_y(double scale_y);
  virtual void set_scale_z(double scale_z);
};
#endif // ifndef CUBE_HPP
