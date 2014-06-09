#include "include/gl_vec.hpp"

template <>
const GLVector<XYZW> GLVector<XYZW>::XVec(1, 0, 0, 0);
template <>
const GLVector<XYZW> GLVector<XYZW>::YVec(0, 1, 0, 0);
template <>
const GLVector<XYZW> GLVector<XYZW>::ZVec(0, 0, 1, 0);
template <>
const GLVector<XYZW> GLVector<XYZW>::NVec(0, 0, 0, 0);

template <>
const GLVector<XYZ> GLVector<XYZ>::XVec(1, 0, 0);
template <>
const GLVector<XYZ> GLVector<XYZ>::YVec(0, 1, 0);
template <>
const GLVector<XYZ> GLVector<XYZ>::ZVec(0, 0, 1);
template <>
const GLVector<XYZ> GLVector<XYZ>::NVec(0, 0, 0);
