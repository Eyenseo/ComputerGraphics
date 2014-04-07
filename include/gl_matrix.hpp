#ifndef GLMATRIX_HPP
#define GLMATRIX_HPP

#include <GL/gl.h>
#include <type_traits>

#include <assert.h>
#include <iostream>

class GLMatrix {
  GLfloat* mat_;

public:

  static const unsigned char COL_LENGTH = 4;
  static const unsigned char ROW_LENGTH = 4;

  GLMatrix() {
    mat_ = new GLfloat[COL_LENGTH * ROW_LENGTH];
  }

  // copy constructor
  GLMatrix(const GLMatrix& copy) {
    mat_ = new GLfloat[COL_LENGTH * ROW_LENGTH];

    for(unsigned char i = 0; i < ROW_LENGTH; ++i) {
      for(unsigned char j = 0; j < COL_LENGTH; ++j) {
        set_data(i, j, copy.get_data(j, i));
      }
    }
  }

  // Destructor
  ~GLMatrix() {
    delete[]mat_;
  }

  // returns the GLMatrix transposed
  GLMatrix transpose() const {
    GLMatrix ret;

    for(unsigned char i = 0; i < ROW_LENGTH; i++) {
      for(unsigned char j = 0; j < COL_LENGTH; j++) {
        ret.set_data(i, j, get_data(j, i));
      }
    }
    return ret;
  }

  // sets the data at m, n with value of data
  inline void set_data(const unsigned char m, const unsigned char n,
                       const GLfloat data) {
    assert(m < ROW_LENGTH && m < COL_LENGTH);
    set_data(m, n, data);
  }

  operator const GLfloat*() const {
    return mat_;
  }

  operator GLfloat*() {
    return mat_;
  }

  // returns the data at m, n
  inline GLfloat get_data(const unsigned char m, const unsigned char n) const {
    assert(m < ROW_LENGTH && m < COL_LENGTH);
    return mat_[m + n * 4];
  }

  const GLMatrix operator+=(const GLMatrix& rhs) {
    for(unsigned int i = 0; i < ROW_LENGTH; i++) {
      for(unsigned int j = 0; j < COL_LENGTH; j++) {
        set_data(i, j, get_data(i, j) + rhs.get_data(i, j));
      }
    }
    return *this;
  }

  friend GLMatrix operator+(GLMatrix lhs, const GLMatrix& rhs) {
    lhs += rhs;
    return lhs;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  const GLMatrix operator+=(const T rhs) {
    for(unsigned int i = 0; i < ROW_LENGTH; i++) {
      for(unsigned int j = 0; j < COL_LENGTH; j++) {
        set_data(i, j, get_data(i, j) + rhs);
      }
    }
    return *this;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  friend GLMatrix operator+(GLMatrix lhs, const T rhs) {
    lhs += rhs;
    return lhs;
  }

  const GLMatrix operator-=(const GLMatrix& rhs) {
    for(unsigned int i = 0; i < ROW_LENGTH; i++) {
      for(unsigned int j = 0; j < COL_LENGTH; j++) {
        set_data(i, j, get_data(i, j) - rhs.get_data(i, j));
      }
    }
    return *this;
  }

  friend GLMatrix operator-(GLMatrix lhs, const GLMatrix& rhs) {
    lhs -= rhs;
    return lhs;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  const GLMatrix operator-=(const T rhs) {
    for(unsigned int i = 0; i < ROW_LENGTH; i++) {
      for(unsigned int j = 0; j < COL_LENGTH; j++) {
        set_data(i, j, get_data(i, j) - rhs);
      }
    }
    return *this;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  friend GLMatrix operator-(GLMatrix lhs, const T rhs) {
    lhs -= rhs;
    return lhs;
  }

  const GLMatrix operator*=(const GLMatrix& rhs) {
    GLfloat  res;
    GLfloat* temp = mat_;

    mat_ = new GLfloat[COL_LENGTH * ROW_LENGTH];

    for(unsigned int i = 0; i < ROW_LENGTH; i++) {
      for(unsigned int j = 0; j < rhs.COL_LENGTH; j++) {
        res = 0;
        for(unsigned int k = 0; k < COL_LENGTH; k++) {
          res += temp[i + k * 4] * rhs.get_data(k, j);
        }
        set_data(i, j, res);
      }
    }

    delete temp;
    return *this;
  }

  friend GLMatrix operator*(GLMatrix lhs, const GLMatrix& rhs) {
    lhs *= rhs;
    return lhs;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  const GLMatrix operator*=(const T rhs) {
    for(unsigned int i = 0; i < COL_LENGTH; i++) {
      for(unsigned int j = 0; j < ROW_LENGTH; j++) {
        set_data(i, j, get_data(i, j) * rhs);
      }
    }
    return *this;
  }

  template<typename T, typename
             = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
  friend GLMatrix operator*(GLMatrix lhs, const T rhs) {
    lhs *= rhs;
    return lhs;
  }
};
#endif // ifndef GLMatrix_HPP
