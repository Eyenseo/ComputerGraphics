#ifndef GLVECTOR_HPP
#define GLVECTOR_HPP

#include <GL/gl.h>
#include <assert.h>
#include <iostream>
#include <math.h>

#include "include/gl_matrix.hpp"

enum GLVectorType {
  XYZ  = 3,
  XYZW = 4
};

template<GLVectorType T>class GLVector {
  const GLVectorType type_;
  GLfloat* vec_;

public:

  GLVector()
    : type_(T),
    vec_(new GLfloat[type_]) {
    for(int i = 0; i < type_; i++) {
      vec_[i] = 0;
    }
  }

  explicit GLVector(const float* copy)
    : type_(T),
    vec_(new GLfloat[type_]) {
    assert(sizeof *copy / sizeof(GLfloat) == type_);

    for(int i = 0; i < type_; i++) {
      vec_[i] = copy[i];
    }
  }

  GLVector(const GLVector& rhs)
    : type_(T),
    vec_(new GLfloat[type_]) {
    for(int i = 0; i < type_; i++) {
      vec_[i] = rhs.vec_[i];
    }
  }

  template<GLVectorType U = T, typename
             = typename std::enable_if<U == XYZ>::type>
  GLVector(float x, float y, float z)
    : type_(T),
    vec_(new GLfloat[type_]) {
    vec_[0] = x;
    vec_[1] = y;
    vec_[2] = z;
  }

  template<GLVectorType U = T, typename
             = typename std::enable_if<U == XYZW>::type>
  GLVector(float x, float y, float z, float w)
    : type_(T),
    vec_(new GLfloat[type_]) {
    vec_[0] = x;
    vec_[1] = y;
    vec_[2] = z;
    vec_[3] = w;
  }

  ~GLVector() {
    delete[]vec_;
  }

  double Length() const {
    double r = 0;

    for(int i = 0; i < type_; i++) {
      r += vec_[i] * vec_[i];
    }
    return sqrt(r);
  }

  double Length2() const {
    double r = 0;

    for(int i = 0; i < type_; i++) {
      r += vec_[i] * vec_[i];
    }
    return r;
  }

  double LengthXY() const {
    return sqrt(vec_[0] * vec_[0] + vec_[1] * vec_[1]);
  }

  double LengthXY2() const {
    return vec_[0] * vec_[0] + vec_[1] * vec_[1];
  }

  double DotXY(const GLVector& rhs) const {
    return vec_[0] * rhs.vec_[0] + vec_[1] * rhs.vec_[1];
  }

  double CrossXY(const GLVector& rhs) const {
    return vec_[0] * rhs.vec_[1] - vec_[1] * rhs.vec_[0];
  }

  void   MinMaxExpand(GLVector& min, GLVector& max) const {
    for(int i = 0; i < type_; i++) {
      if(vec_[i] < min.vec_[i]) min.vec_[i] = vec_[i];
      if(vec_[i] > max.vec_[i]) max.vec_[i] = vec_[i];
    }
  }

  void   Normalize() {
    double l = 1.0 / Length();

    for(int i = 0; i < type_; i++)
      vec_[i] *= l;
  }

  const GLfloat* get_vector() const {
    return vec_;
  }

  GLfloat& operator[](const unsigned int index) {
    assert(index < type_);
    return vec_[index];
  }

  const GLfloat& operator[](const unsigned int index) const {
    assert(index < type_);
    return vec_[index];
  }

  GLVector& operator=(const GLVector& rhs) {
    for(int i = 0; i < type_; i++) {
      vec_[i] = rhs.vec_[i];
    }
    return *this;
  }

  GLVector& operator+=(const float rhs) {
    for(int i = 0; i < type_; i++) {
      vec_[i] += rhs;
    }
    return *this;
  }

  inline friend GLVector operator+(GLVector lhs, const float rhs) {
    return lhs += rhs;
  }

  inline friend GLVector operator+(float rhs, GLVector lhs) {
    return lhs += rhs;
  }

  GLVector& operator+=(const GLVector& rhs) {
    for(int i = 0; i < type_; i++) {
      vec_[i] += rhs.vec_[i];
    }
    return *this;
  }

  inline friend GLVector operator+(GLVector lhs, const GLVector& rhs) {
    return lhs += rhs;
  }

  GLVector& operator-=(const float rhs) {
    for(int i = 0; i < type_; i++) {
      vec_[i] -= rhs;
    }
    return *this;
  }

  inline friend GLVector operator-(GLVector lhs, const float rhs) {
    return lhs -= rhs;
  }

  inline friend GLVector operator-(float rhs, GLVector lhs) {
    return lhs -= rhs;
  }

  GLVector& operator-=(const GLVector& rhs) {
    for(int i = 0; i < type_; i++) {
      vec_[i] -= rhs.vec_[i];
    }
    return *this;
  }

  inline friend GLVector operator-(GLVector lhs, const GLVector& rhs) {
    return lhs -= rhs;
  }

  inline friend GLVector operator-(GLVector lhs) {
    GLVector c;

    for(int i = 0; i < lhs.type_; i++) {
      c.vec_[i] = -lhs.vec_[i];
    }
    return c;
  }

  GLVector& operator*=(float sc) {
    for(int i = 0; i < type_; i++) {
      vec_[i] *= sc;
    }
    return *this;
  }

  inline friend GLVector operator*(float sc, GLVector lhs) {
    return lhs *= sc;
  }

  inline friend GLVector operator*(GLVector lhs, float sc) {
    return lhs *= sc;
  }

  template<GLVectorType U = T, typename
             = typename std::enable_if<U == XYZW>::type>
  friend GLVector operator*(const GLMatrix& lhs, const GLVector& rhs) {
    // The SFINAE only allows XYZW
    GLVector res;

    for(unsigned char i = 0; i < lhs.ROW_LENGTH; ++i) {
      for(unsigned char j = 0; j < lhs.COL_LENGTH; ++j) {
        res.vec_[i] += lhs.get_data(i, j) * rhs.vec_[j];
      }
    }

    return res;
  }

  GLVector& operator/=(float sc) {
    for(int i = 0; i < type_; i++) {
      vec_[i] /= sc;
    }
    return *this;
  }

  inline friend GLVector operator/(GLVector lhs, float sc) {
    return lhs /= sc;
  }

  inline friend GLVector operator/(float sc, GLVector lhs) {
    return lhs /= sc;
  }

  operator const GLfloat*() const {
    return vec_;
  }

  template<GLVectorType U = T, typename
             = typename std::enable_if<U == XYZW>::type>
  operator GLVector<XYZ>() const {
    return GLVector<XYZ>(vec_[0], vec_[1], vec_[2]);
  }

  // dot product ////////////////////////////////////////////////
  float operator*=(const GLVector& rhs) {
    double r = 0;

    for(int i = 0; i < type_; i++) {
      r += vec_[i] * rhs.vec_[i];
    }
    return r;
  }

  inline friend float operator*(GLVector lhs, const GLVector& rhs) {
    return lhs *= rhs;
  }

  // cross product //////////////////////////////////////////////
  template<GLVectorType U = T, typename
             = typename std::enable_if<U == XYZW>::type>
  inline friend GLVector<XYZ>operator%(const GLVector& lhs,
                                       const GLVector& rhs) {
    GLVector ret;

    ret[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    ret[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    ret[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return ret;
  }
};
#endif // ifndef GLVECTOR_HPP
