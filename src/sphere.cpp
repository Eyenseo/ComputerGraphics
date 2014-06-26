#include <GL/glew.h>

#include "include/sphere.hpp"

#include <fstream>
#include <string>
Sphere::Sphere()
    : Drawable()
    , Hitable()
    , resolution_(64)
    , vertices_size_(resolution_ * (resolution_ + 1) * 2 * 3 * 3)
    , normals_size_(vertices_size_)
    , vboID_(0)
    , sb_(nullptr)
    , vertices_(new GLfloat[vertices_size_])
    , normals_(new GLfloat[normals_size_]) {
}

Sphere::Sphere(double origin_x, double origin_y, double origin_z)
    : Drawable(origin_x, origin_y, origin_z, 1)
    , Hitable()
    , resolution_(64)
    , vertices_size_(resolution_ * (resolution_ + 1) * 2 * 3 * 3)
    , normals_size_(vertices_size_)
    , vboID_(0)
    , sb_(nullptr)
    , vertices_(new GLfloat[vertices_size_])
    , normals_(new GLfloat[normals_size_]) {
  sb_ = new SphereBB(this, &origin_, .5);
  add_bounding_box(sb_);

  glGenBuffers(1, &vboID_);
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glBufferData(GL_ARRAY_BUFFER,
               (vertices_size_ + normals_size_) * sizeof(float), 0,
               GL_STATIC_DRAW);
  update_geometry();
}

Sphere::Sphere(double origin_x, double origin_y, double origin_z,
               unsigned char colors)
    : Drawable(origin_x, origin_y, origin_z, colors)
    , Hitable()
    , resolution_(64)
    , vertices_size_(resolution_ * (resolution_ + 1) * 2 * 3 * 3)
    , normals_size_(vertices_size_)
    , vboID_(0)
    , sb_(nullptr)
    , vertices_(new GLfloat[vertices_size_])
    , normals_(new GLfloat[normals_size_]) {
  sb_ = new SphereBB(this, &origin_, .5);
  add_bounding_box(sb_);

  glGenBuffers(1, &vboID_);
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glBufferData(GL_ARRAY_BUFFER,
               (vertices_size_ + normals_size_) * sizeof(float), 0,
               GL_STATIC_DRAW);
  update_geometry();
}

Sphere::~Sphere() {
  delete sb_;
  delete[] vertices_;
  delete[] normals_;
  glDeleteBuffers(1, &vboID_);
}

void Sphere::step() {
  if(moveable_) {
    // TODO review slow speeds are a problem on edges
    speed_ += GLVector<XYZW>::ZVec * -9.81 * 0.016666 + (speed_ * -fraction_);
    origin_ += speed_ * 0.016666;
  }
}

void Sphere::load_shader(const char* filename, GLuint& shader, bool vertex) {
  std::fstream file;
  file.open(filename, std::ios::in | std::ios::binary);

  if(!file.is_open()) {
    std::cout << "File isn't open!" << std::endl;
    throw std::exception();
  } else {
    file.seekg(0, file.end);
    unsigned int length = file.tellg();
    file.seekg(0, file.beg);
    char* file_buffer = new char[length];
    file.read(file_buffer, length);
    file.close();
    const char* source = file_buffer;

    if(vertex) {
      shader = glCreateShader(GL_VERTEX_SHADER);
    } else {
      shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE) {
      char buffer[512];
      glGetShaderInfoLog(shader, 512, NULL, buffer);
      std::cout << buffer << std::endl;
      assert(false);
    }
  }
}


void Sphere::draw() {
  static bool once = true;
  static GLuint vertex_shader = 0;
  static GLuint fragment_shader = 0;
  static GLuint shader_program = 0;
  if(once) {
    // load_shader("point_light_per_pixel.vert", vertex_shader, true);
    // load_shader("point_light_per_pixel.frag", fragment_shader, false);
    load_shader("directional_light_per_pixel.vert", vertex_shader, true);
    load_shader("directional_light_per_pixel.frag", fragment_shader, false);
    // load_shader("per_pixel_lighting.vert", vertex_shader,true);
    // load_shader("per_pixel_lighting.frag", fragment_shader,false);

    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    once = false;
  }

  glDisable(GL_LIGHTING);
  glUseProgram(shader_program);
  set_material_color(1, 0);

  // set_material_color(1, 0);
  glEnable(GL_NORMALIZE);
  // glShadeModel(GL_SMOOTH);

  rotate_from(rotation_[0], rotation_[1], rotation_[2], origin_[0], origin_[1],
              origin_[2]);
  glScalef(scale_[0], scale_[1], scale_[2]);


  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  // glPointSize(4);

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  // glEnableClientState(GL_COLOR_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, 0);
  glNormalPointer(GL_FLOAT, 0, (void*)(sizeof(normals_)));
  // glColorPointer(3, GL_FLOAT, 0,
  // (void*)(sizeof(vertices)+sizeof(normals)));

  // glDrawArrays(GL_POINTS, 0, vertices_size_ / 3);
  glDrawArrays(GL_TRIANGLES, 0, vertices_size_ / 3);

  // glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glPopMatrix();
  glUseProgram(0);
  glEnable(GL_LIGHTING);
}

void Sphere::update_geometry() {
#ifndef M_PI
#define M_PI 3.14159265359
#endif
  const double a1d = M_PI / resolution_;
  const double a2d = M_PI / resolution_;
  unsigned int index = 0;

  for(int i = 0; i < resolution_; i++) {
    const double a1 = i * a1d;
    for(int j = 0; j <= resolution_; j++) {
      for(int k = 0; k < 2; k++) {
        {
          const double a2 = (j + .5 * (i % 2) + k) * 2 * a2d;
          {
            const double s1 = sin(a1 + a1d * k);
            const double c1 = cos(a1 + a1d * k);
            const double s2 = sin(a2 + a2d * k);
            const double c2 = cos(a2 + a2d * k);
            const GLVector<XYZW> normal = c1 * GLVector<XYZW>::XVec
                                          + s1 * (c2 * GLVector<XYZW>::YVec
                                                  + s2 * GLVector<XYZW>::ZVec);

            for(unsigned int i = 0; i < 3; ++i) {
              normals_[index] = normal[i];
              vertices_[index] = .5 * normal[i];
              ++index;
            }
          }
          {
            const double s1 = sin(a1 + a1d * ((k + 1) % 2));
            const double c1 = cos(a1 + a1d * ((k + 1) % 2));
            const double s2 = sin(a2 + a2d * ((k + 1) % 2));
            const double c2 = cos(a2 + a2d * ((k + 1) % 2));
            const GLVector<XYZW> normal = c1 * GLVector<XYZW>::XVec
                                          + s1 * (c2 * GLVector<XYZW>::YVec
                                                  + s2 * GLVector<XYZW>::ZVec);

            for(unsigned int i = 0; i < 3; ++i) {
              normals_[index] = normal[i];
              vertices_[index] = .5 * normal[i];
              ++index;
            }
          }
        }
        {
          const double a2 = (j + .5 * (i % 2) + ((k + 1) % 2)) * 2 * a2d;

          const double s1 = sin(a1 + a1d * k);
          const double c1 = cos(a1 + a1d * k);
          const double s2 = sin(a2 + a2d * k);
          const double c2 = cos(a2 + a2d * k);
          const GLVector<XYZW> normal
              = c1 * GLVector<XYZW>::XVec
                + s1 * (c2 * GLVector<XYZW>::YVec + s2 * GLVector<XYZW>::ZVec);

          for(unsigned int i = 0; i < 3; ++i) {
            normals_[index] = normal[i];
            vertices_[index] = .5 * normal[i];
            ++index;
          }
        }
      }
    }
  }
  glBindBuffer(GL_ARRAY_BUFFER, vboID_);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * vertices_size_,
                  vertices_);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * vertices_size_,
                  sizeof(float) * normals_size_, normals_);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::set_scale(const GLVector<XYZ>& scale) {
  set_scale(scale[0], scale[1], scale[2]);
  sb_->update_scale(scale_);
}

void Sphere::set_scale(double scale) {
  Drawable::set_scale(scale, scale, scale);
  sb_->update_scale(scale_);
}

void Sphere::set_scale(double scale_x, double, double) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_x(double scale_x) {
  Drawable::set_scale(scale_x, scale_x, scale_x);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_y(double scale_y) {
  Drawable::set_scale(scale_y, scale_y, scale_y);
  sb_->update_scale(scale_);
}

void Sphere::set_scale_z(double scale_z) {
  Drawable::set_scale(scale_z, scale_z, scale_z);
  sb_->update_scale(scale_);
}
