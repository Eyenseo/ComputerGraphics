#ifndef Button_HPP
#define Button_HPP value

#include "drawable.hpp"

#include <functional>

class Button : public Drawable {
protected:
  GLuint image_id_;
  unsigned int width_;
  unsigned int height_;
  std::function<void()> on_press_;
  std::function<void()> on_click_;
  std::function<void()> on_release_;
  bool pressed_;
  GLVector<XYZW>& origin_ = Drawable::origin_;

  virtual void load_bmp(const char* imagepath);
  GLVector<XYZW> mouse_pos_to_world(const GLMatrix& modelXprojectionINV,
                                    GLint* viewport, GLVector<XYZW> pos);

public:
  Button();
  Button(unsigned int origin_x, unsigned int origin_y, const char* image_path);
  virtual ~Button();

  virtual void draw();

  virtual void set_image(GLuint image);

  virtual void on_press(unsigned int x, unsigned int y);
  virtual void on_release(unsigned int x, unsigned int y);
  virtual void on_click(unsigned int x, unsigned int y);

  virtual void set_on_press(const std::function<void()>& f);
  virtual void set_on_release(const std::function<void()>& f);
  virtual void set_on_click(const std::function<void()>& f);

  virtual void set_pressed(bool pressed);

};
#endif
