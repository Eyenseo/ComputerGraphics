#include "include/button.hpp"

#include <iostream>
#include <sstream>
#include <exception>

Button::Button()
    : Drawable()
    , width_(0)
    , height_(0)
    , on_press_([]() {})
    , on_release_([]() {})
    , pressed_(false) {
}

Button::Button(unsigned int origin_x, unsigned int origin_y,
               const char* image_path)
    : Drawable(origin_x, origin_y, 0, 2)
    , width_(0)
    , height_(0)
    , on_press_([]() {})
    , on_release_([]() {})
    , pressed_(false) {
  load_bmp(image_path);
}

Button::~Button() {
  glDeleteTextures(1, &image_id_);
}

// I don't know where this was taken from ...
void Button::load_bmp(const char* imagepath) {
  // Data read from the header of the BMP file
  unsigned char header[54];  // Each BMP file begins by a 54-bytes header
  unsigned int dataPos;  // Position in the file where the actual data begins
  unsigned int imageSize;
  // Actual RGB data
  unsigned char* data;

  // Open the file
  FILE* file = fopen(imagepath, "rb");
  if(!file) {
    printf("Image could not be opened\n");
    throw std::exception();
  }
  if(fread(header, 1, 54, file) != 54) {  // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    throw std::exception();
  }
  if(header[0] != 'B' || header[1] != 'M') {
    printf("Not a correct BMP file\n");
    throw std::exception();
  }

  // Read ints from the byte array
  dataPos = *(int*)&(header[0x0A]);
  imageSize = *(int*)&(header[0x22]);
  width_ = *(int*)&(header[0x12]);
  height_ = *(int*)&(header[0x16]);

  // Some BMP files are misformatted, guess missing information
  if(imageSize == 0) {
    // 3 : one byte for each Red, Green and Blue component
    imageSize = width_ * height_ * 3;
  }
  if(dataPos == 0) {
    // The BMP header is done that way
    dataPos = 54;
  }

  // Create a buffer
  data = new unsigned char[imageSize];

  // Read the actual data from the file into the buffer
  fread(data, 1, imageSize, file);

  // Everything is in memory now, the file can be closed
  fclose(file);

  // Create one OpenGL texture
  glGenTextures(1, &image_id_);

  glEnable(GL_TEXTURE_2D);
  // "Bind" the newly created texture : all future texture functions will
  // modify this texture
  glBindTexture(GL_TEXTURE_2D, image_id_);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  // Give the image to OpenGL
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);

  glDisable(GL_TEXTURE_2D);
  delete[] data;
}

GLVector<XYZW> Button::mouse_pos_to_world(const GLMatrix& modelXprojectionINV,
                                          GLint* viewport, GLVector<XYZW> pos) {
  pos[1] = viewport[3] - pos[1];

  // Transformation of normalized coordinates between -1 and 1
  pos[0] = ((pos[0] - viewport[0]) / viewport[2]) * 2.0 - 1.0;
  pos[1] = ((pos[1] - viewport[1]) / viewport[3]) * 2.0 - 1.0;
  pos[2] = pos[2] * 2.0 - 1.0;
  pos[3] = 1.0;

  GLVector<XYZW> res = modelXprojectionINV * pos;

  assert(res[3] != 0);

  res[0] /= res[3];
  res[1] /= res[3];
  res[2] /= res[3];
  return res;
}

void Button::draw() {
  GLMatrix model;
  glGetDoublev(GL_MODELVIEW_MATRIX, model);

  // Retrieve projection matrix
  GLMatrix projection;
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  GLMatrix mp = model.transpose() * projection.transpose();

  if(mp.inverse()) {
    const GLVector<XYZW> clip = projection * GLVector<XYZW>::ZVec * 0.00001;

    // Retrieve viewport matrix
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLVector<XYZW> left_top(origin_[0], origin_[1], 0, 0);
    GLVector<XYZW> left_bottom(origin_[0], origin_[1] + height_ * scale_[1], 0,
                               0);
    GLVector<XYZW> right_bottom(origin_[0] + width_ * scale_[0],
                                origin_[1] + height_ * scale_[1], 0, 0);
    GLVector<XYZW> right_top(origin_[0] + width_ * scale_[0], origin_[1], 0, 0);

    left_top = mouse_pos_to_world(mp, viewport, left_top);
    left_bottom = mouse_pos_to_world(mp, viewport, left_bottom);
    right_bottom = mouse_pos_to_world(mp, viewport, right_bottom);
    right_top = mouse_pos_to_world(mp, viewport, right_top);

    GLVector<XYZ> normal = (const GLVector<XYZ>)(left_bottom - left_top)
                           % (const GLVector<XYZ>)(right_bottom - left_top);
    normal.Normalize();

    if(!pressed_) {
      glColor3f(color_[0], color_[1], color_[2]);
    } else {
      glColor3f(color_[3], color_[4], color_[5]);
    }

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);  // Enable texture
    glBindTexture(GL_TEXTURE_2D, image_id_);
    glBegin(GL_QUADS);
    glNormal3dv(normal);
    glTexCoord2f(0, 1);
    glVertex3dv(left_top +clip);
    glTexCoord2f(0, 0);
    glVertex3dv(left_bottom +clip);
    glTexCoord2f(1, 0);
    glVertex3dv(right_bottom +clip);
    glTexCoord2f(1, 1);
    glVertex3dv(right_top +clip);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
  }
  glPopMatrix();
}

void Button::set_image(GLuint image) {
  image_id_ = image;
}

void Button::on_press(unsigned int x, unsigned int y) {
  if(x > origin_[0] && y > origin_[1] && x < origin_[0] + width_ * scale_[0]
     && y < origin_[1] + height_ * scale_[1]) {
    pressed_ = true;
    on_press_();
  }
}

void Button::on_release(unsigned int x, unsigned int y) {
  if(pressed_ && x > origin_[0] && y > origin_[1]
     && x < origin_[0] + width_ * scale_[0]
     && y < origin_[1] + height_ * scale_[1]) {
    on_release_();
  }
}

void Button::set_on_press(const std::function<void()>& f) {
  on_press_ = f;
}

void Button::set_on_release(const std::function<void()>& f) {
  on_release_ = f;
}

void Button::set_pressed(bool pressed) {
  pressed_ = pressed;
}
