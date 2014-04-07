#ifndef TABLE_HPP
#define TABLE_HPP value

#include "drawable.hpp"

class Table : public Drawable {
  struct InnerOBB {
    
  };



  const float inner_table_height_ = 5;
  const float inner_table_length_ = 14;
  const float inner_table_width_  = 10;

  const float plank_height_ = 0.1;

  const float border_height_ = 0.7;
  const float border_width_  = 0.5;




  void short_border();
  void long_border();
  void plank();
  void legs();
  void face(const GLVector<XYZW>& v1, const GLVector<XYZW>& v2,
            const GLVector<XYZW>& v3, const GLVector<XYZW>& v4);

public:

  Table();
  Table(float origin_x, float origin_y, float origin_z);
  Table(float origin_x, float origin_y, float origin_z, unsigned char colors);
  ~Table();

  virtual void draw();
};
#endif // ifndef CUBE_HPP
