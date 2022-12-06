//
// Created by xukq on 22/12/05.
//
#include "math/Vec3.h"

namespace Tracer {
std::istream &operator>>(std::istream &is, Vec3 &v) {
  is >> v.data[0] >> v.data[1] >> v.data[2];
  return is;
}
std::ostream &operator<<(std::ostream &os, const Vec3 &v) {
  os << v[0] << ' ' << v[1] << ' ' << v[2];
  return os;
}

Vec3 &Vec3::operator+=(const Vec3 &rhs) {
  this->data[0] += rhs[0];
  this->data[1] += rhs[1];
  this->data[2] += rhs[2];
  return *this;
}
Vec3 &Vec3::operator-=(const Vec3 &rhs) {
  this->data[0] -= rhs[0];
  this->data[1] -= rhs[1];
  this->data[2] -= rhs[2];
  return *this;
}
Vec3 &Vec3::operator*=(const Vec3 &rhs) {
  this->data[0] *= rhs[0];
  this->data[1] *= rhs[1];
  this->data[2] *= rhs[2];
  return *this;
}
Vec3 &Vec3::operator/=(const Vec3 &rhs) {
  this->data[0] /= rhs[0];
  this->data[1] /= rhs[1];
  this->data[2] /= rhs[2];
  return *this;
}
Vec3 &Vec3::operator*=(const float rhs) {
  this->data[0] *= rhs;
  this->data[1] *= rhs;
  this->data[2] *= rhs;
  return *this;
}
Vec3 &Vec3::operator/=(const float rhs) {
  this->data[0] /= rhs;
  this->data[1] /= rhs;
  this->data[2] /= rhs;
  return *this;
}

Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs) { return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]}; }
Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs) { return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]}; }
Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs) { return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]}; }
Vec3 operator/(const Vec3 &lhs, const Vec3 &rhs) { return {lhs[0] / rhs[0], lhs[1] / rhs[1], lhs[2] / rhs[2]}; }
Vec3 operator*(const Vec3 &lhs, float rhs) { return {lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs}; }
Vec3 operator/(const Vec3 &lhs, float rhs) { return {lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs}; }
Vec3 operator*(float lhs, const Vec3 &rhs) { return rhs * lhs; }

[[maybe_unused]] float dot(const Vec3 &lhs, const Vec3 &rhs) {
  return lhs[0] * rhs[0] + lhs[1] * rhs[0] + lhs[2] * rhs[2];
}
[[maybe_unused]] Vec3 cross(const Vec3 &lhs, const Vec3 &rhs) {
  return {
	  lhs[1] * rhs[2] - lhs[2] * rhs[1],
	  lhs[2] * rhs[0] - lhs[0] * rhs[2],
	  lhs[0] * rhs[1] - lhs[1] * rhs[0]
  };
}
Vec3 normalize(const Vec3 &v) {
  return Vec3(v).normalized();
}
}
