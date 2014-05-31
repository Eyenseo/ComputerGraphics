#ifndef GLMATRIX_HPP
#define GLMATRIX_HPP

#include <GL/gl.h>
#include <type_traits>

#include <assert.h>
#include <iostream>

class GLMatrix {
  GLdouble* mat_;

public:

  static const unsigned char COL_LENGTH = 4;
  static const unsigned char ROW_LENGTH = 4;

  GLMatrix() {
    mat_ = new GLdouble[COL_LENGTH * ROW_LENGTH];

    for(unsigned char i = 0; i < ROW_LENGTH; ++i) {
      for(unsigned char j = 0; j < COL_LENGTH; ++j) {
        set_data(i, j, 0);
      }
    }
  }

  // copy constructor
  GLMatrix(const GLMatrix& copy) {
    mat_ = new GLdouble[COL_LENGTH * ROW_LENGTH];

    for(unsigned char i = 0; i < ROW_LENGTH; ++i) {
      for(unsigned char j = 0; j < COL_LENGTH; ++j) {
        set_data(i, j, copy.get_data(i, j));
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

  // taken from GLU
  bool inverse() {
    GLdouble* temp = mat_;

    mat_ = new GLdouble[COL_LENGTH * ROW_LENGTH];

    mat_[0] = temp[5] * temp[10] * temp[15]
              - temp[5] * temp[11] * temp[14]
              - temp[9] * temp[6] * temp[15]
              + temp[9] * temp[7] * temp[14]
              + temp[13] * temp[6] * temp[11]
              - temp[13] * temp[7] * temp[10];

    mat_[4] = -temp[4] * temp[10] * temp[15]
              + temp[4] * temp[11] * temp[14]
              + temp[8] * temp[6] * temp[15]
              - temp[8] * temp[7] * temp[14]
              - temp[12] * temp[6] * temp[11]
              + temp[12] * temp[7] * temp[10];

    mat_[8] = temp[4] * temp[9] * temp[15]
              - temp[4] * temp[11] * temp[13]
              - temp[8] * temp[5] * temp[15]
              + temp[8] * temp[7] * temp[13]
              + temp[12] * temp[5] * temp[11]
              - temp[12] * temp[7] * temp[9];

    mat_[12] = -temp[4] * temp[9] * temp[14]
               + temp[4] * temp[10] * temp[13]
               + temp[8] * temp[5] * temp[14]
               - temp[8] * temp[6] * temp[13]
               - temp[12] * temp[5] * temp[10]
               + temp[12] * temp[6] * temp[9];

    mat_[1] = -temp[1] * temp[10] * temp[15]
              + temp[1] * temp[11] * temp[14]
              + temp[9] * temp[2] * temp[15]
              - temp[9] * temp[3] * temp[14]
              - temp[13] * temp[2] * temp[11]
              + temp[13] * temp[3] * temp[10];

    mat_[5] = temp[0] * temp[10] * temp[15]
              - temp[0] * temp[11] * temp[14]
              - temp[8] * temp[2] * temp[15]
              + temp[8] * temp[3] * temp[14]
              + temp[12] * temp[2] * temp[11]
              - temp[12] * temp[3] * temp[10];

    mat_[9] = -temp[0] * temp[9] * temp[15]
              + temp[0] * temp[11] * temp[13]
              + temp[8] * temp[1] * temp[15]
              - temp[8] * temp[3] * temp[13]
              - temp[12] * temp[1] * temp[11]
              + temp[12] * temp[3] * temp[9];

    mat_[13] = temp[0] * temp[9] * temp[14]
               - temp[0] * temp[10] * temp[13]
               - temp[8] * temp[1] * temp[14]
               + temp[8] * temp[2] * temp[13]
               + temp[12] * temp[1] * temp[10]
               - temp[12] * temp[2] * temp[9];

    mat_[2] = temp[1] * temp[6] * temp[15]
              - temp[1] * temp[7] * temp[14]
              - temp[5] * temp[2] * temp[15]
              + temp[5] * temp[3] * temp[14]
              + temp[13] * temp[2] * temp[7]
              - temp[13] * temp[3] * temp[6];

    mat_[6] = -temp[0] * temp[6] * temp[15]
              + temp[0] * temp[7] * temp[14]
              + temp[4] * temp[2] * temp[15]
              - temp[4] * temp[3] * temp[14]
              - temp[12] * temp[2] * temp[7]
              + temp[12] * temp[3] * temp[6];

    mat_[10] = temp[0] * temp[5] * temp[15]
               - temp[0] * temp[7] * temp[13]
               - temp[4] * temp[1] * temp[15]
               + temp[4] * temp[3] * temp[13]
               + temp[12] * temp[1] * temp[7]
               - temp[12] * temp[3] * temp[5];

    mat_[14] = -temp[0] * temp[5] * temp[14]
               + temp[0] * temp[6] * temp[13]
               + temp[4] * temp[1] * temp[14]
               - temp[4] * temp[2] * temp[13]
               - temp[12] * temp[1] * temp[6]
               + temp[12] * temp[2] * temp[5];

    mat_[3] = -temp[1] * temp[6] * temp[11]
              + temp[1] * temp[7] * temp[10]
              + temp[5] * temp[2] * temp[11]
              - temp[5] * temp[3] * temp[10]
              - temp[9] * temp[2] * temp[7]
              + temp[9] * temp[3] * temp[6];

    mat_[7] = temp[0] * temp[6] * temp[11]
              - temp[0] * temp[7] * temp[10]
              - temp[4] * temp[2] * temp[11]
              + temp[4] * temp[3] * temp[10]
              + temp[8] * temp[2] * temp[7]
              - temp[8] * temp[3] * temp[6];

    mat_[11] = -temp[0] * temp[5] * temp[11]
               + temp[0] * temp[7] * temp[9]
               + temp[4] * temp[1] * temp[11]
               - temp[4] * temp[3] * temp[9]
               - temp[8] * temp[1] * temp[7]
               + temp[8] * temp[3] * temp[5];

    mat_[15] = temp[0] * temp[5] * temp[10]
               - temp[0] * temp[6] * temp[9]
               - temp[4] * temp[1] * temp[10]
               + temp[4] * temp[2] * temp[9]
               + temp[8] * temp[1] * temp[6]
               - temp[8] * temp[2] * temp[5];

    double det;
    int    i;
    det = temp[0] * mat_[0] + temp[1] * mat_[4] + temp[2] * mat_[8]
          + temp[3] * mat_[12];

    if(det == 0.0) {
      delete mat_;
      mat_ = temp;
      return false;
    }

    det = 1.0 / det;

    for(i = 0; i < 16; i++) {
      mat_[i] = mat_[i] * det;
    }
    delete temp;

    return true;
  }

  // sets the data at m, n with value of data
  inline void set_data(const unsigned char m, const unsigned char n,
                       const GLdouble data) {
    assert(m < ROW_LENGTH && m < COL_LENGTH);
    mat_[m + n * 4] = data;
  }

  operator const GLdouble*() const {
    return mat_;
  }

  operator GLdouble*() {
    return mat_;
  }

  // returns the data at m, n
  inline GLdouble get_data(const unsigned char m, const unsigned char n) const {
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
    GLdouble  res  = 0;
    GLdouble* temp = new GLdouble[COL_LENGTH * ROW_LENGTH];

    for(unsigned int i = 0; i < 4; i++) {
      for(unsigned int j = 0; j < 4; j++) {
        for(unsigned int k = 0; k < 4; k++) {
          res += get_data(i, k) * rhs.get_data(k, j);
        }
        temp[i + j * 4] = res;
        res = 0.0;
      }
    }

    delete mat_;
    mat_ = temp;
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

  GLMatrix operator=(const GLMatrix& copy) {
    for(unsigned char i = 0; i < ROW_LENGTH; ++i) {
      for(unsigned char j = 0; j < COL_LENGTH; ++j) {
        set_data(i, j, copy.get_data(i, j));
      }
    }

    return *this;
  }
};
#endif // ifndef GLMatrix_HPP
