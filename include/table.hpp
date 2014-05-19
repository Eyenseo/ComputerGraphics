#ifndef TABLE_HPP
#define TABLE_HPP value

#include "drawable.hpp"
#include "obb.hpp"

class Table : public Drawable, public OBB {
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

public:

  Table();
  Table(double origin_x, double origin_y, double origin_z);
  Table(double origin_x, double origin_y, double origin_z,
        unsigned char colors);
  ~Table();

  virtual void draw();
};
#endif // ifndef CUBE_HPP
