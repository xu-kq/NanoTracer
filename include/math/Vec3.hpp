//
// Created by xukq on 22/12/05.
//
#pragma once
#include <array>
#include <cmath>
#include <iostream>

namespace Tracer {

template<typename T>
class Vec3 {
public:
  Vec3() : data{} {};
  Vec3(const Vec3&) = default;
  Vec3(T e0, T e1, T e2) : data{e0, e1, e2} {}

  template<typename R>
  explicit operator class Vec3<R>() {
  	return {
		static_cast<R>(data[0]),
		static_cast<R>(data[1]),
		static_cast<R>(data[2])
	  };
  }

  [[nodiscard]] T x() const { return data[0]; }
  [[nodiscard]] T y() const { return data[1]; }
  [[nodiscard]] T z() const { return data[2]; }

  Vec3 operator-() const { return {-x(), -y(), -z()}; }
  T operator[](int i) const { return data[i]; }
  T &operator[](int i) { return data[i]; }

  [[nodiscard]] T length() const { return std::sqrt(squared_length()); }
  [[nodiscard]] T squared_length() const { return data[0] * data[0] + data[1] * data[1] + data[2] * data[2]; }
  Vec3 &normalized() { return *this /= length(); }

  Vec3 &operator+=(const Vec3 &rhs);
  Vec3 &operator-=(const Vec3 &rhs);
  Vec3 &operator*=(T rhs);
  Vec3 &operator/=(T rhs);

private:
  std::array<T, 3> data;
};

// type alias for Vec3<T>
using Vec3i [[maybe_unused]] = Vec3<int>;
using Color3 = Vec3<int>;
using Vec3d = Vec3<double>;

// Implementation of member function: self arithmetic operator
template<typename T> auto Vec3<T>::operator+=(const Vec3 &rhs)  -> Vec3 &  {
  this->data[0] += rhs[0];
  this->data[1] += rhs[1];
  this->data[2] += rhs[2];
  return *this;
}
template<typename T> auto Vec3<T>::operator-=(const Vec3 &rhs) -> Vec3 & {
  this->data[0] -= rhs[0];
  this->data[1] -= rhs[1];
  this->data[2] -= rhs[2];
  return *this;
}
template<typename T> auto Vec3<T>::operator*=(const T rhs) -> Vec3 &  {
  this->data[0] *= rhs;
  this->data[1] *= rhs;
  this->data[2] *= rhs;
  return *this;
}
template<typename T> auto Vec3<T>::operator/=(const T rhs) -> Vec3 &  {
  this->data[0] /= rhs;
  this->data[1] /= rhs;
  this->data[2] /= rhs;
  return *this;
}

// Utility function: arithmetic operator
template<typename T> auto operator+(const Vec3<T> &lhs, const Vec3<T> &rhs) -> Vec3<T> {
  return {lhs[0] + rhs[0], lhs[1] + rhs[1], lhs[2] + rhs[2]};
}
template<typename T> auto operator-(const Vec3<T> &lhs, const Vec3<T> &rhs) -> Vec3<T> {
  return {lhs[0] - rhs[0], lhs[1] - rhs[1], lhs[2] - rhs[2]};
}

// Utility function: bit-wise product
template<typename T> auto operator*(const Vec3<T> &lhs, const Vec3<T> &rhs) -> Vec3<T> {
  return {lhs[0] * rhs[0], lhs[1] * rhs[1], lhs[2] * rhs[2]};
}

// Utility function: vector manipulation
template<typename T> auto operator*(const Vec3<T> &lhs, T rhs) -> Vec3<T> {
  return {lhs[0] * rhs, lhs[1] * rhs, lhs[2] * rhs};
}
template<typename T> auto operator*(T lhs, const Vec3<T> &rhs) -> Vec3<T> {
  return rhs * lhs;
}
template<typename T> auto operator/(const Vec3<T> &lhs, T rhs) -> Vec3<T> {
  return {lhs[0] / rhs, lhs[1] / rhs, lhs[2] / rhs};
}
template<typename T> auto dot(const Vec3<T> &lhs, const Vec3<T> &rhs) -> T {
  return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}
template<typename T> [[maybe_unused]] auto cross(const Vec3<T> &lhs, const Vec3<T> &rhs) -> Vec3<T> {
  return {
	  lhs[1] * rhs[2] - lhs[2] * rhs[1],
	  lhs[2] * rhs[0] - lhs[0] * rhs[2],
	  lhs[0] * rhs[1] - lhs[1] * rhs[0]
  };
}
template<typename T> auto normalize(const Vec3<T> &v) -> Vec3<T> { return Vec3<T>(v).normalized(); }

// Utility function: pretty print
template<typename T> auto operator<<(std::ostream &os, const Vec3<T> &v) -> std::ostream & {
  os << v[0] << ' ' << v[1] << ' ' << v[2];
  return os;
}

}    // Tracer

