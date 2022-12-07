//
// Created by xukq on 22/12/05.
//
#pragma once
#include <array>
#include <cmath>
#include <iostream>

namespace Tracer {

class Vec3 {
public:
  Vec3() = default;
  Vec3(float e0, float e1, float e2) : data{e0, e1, e2} {}

  [[nodiscard]] float x() const { return data[0]; }
  [[nodiscard]] float y() const { return data[1]; }
  [[nodiscard]] float z() const { return data[2]; }
  [[nodiscard]] float r() const { return data[0]; }
  [[nodiscard]] float g() const { return data[1]; }
  [[nodiscard]] float b() const { return data[2]; }

  const Vec3 &operator+() const { return *this; }
  Vec3 operator-() const { return {-x(), -y(), -z()}; }
  float operator[](int i) const { return data[i]; }

  [[nodiscard]] float length() const { return std::sqrt(squared_length()); }
  [[nodiscard]] float squared_length() const { return data[0] * data[0] + data[1] * data[1] + data[2] * data[2]; }
  Vec3 &normalized() { return *this /= length(); }


  Vec3 &operator+=(const Vec3 &rhs);
  Vec3 &operator-=(const Vec3 &rhs);
  Vec3 &operator*=(const Vec3 &rhs);
  Vec3 &operator/=(const Vec3 &rhs);
  Vec3 &operator*=(float rhs);
  Vec3 &operator/=(float rhs);

  friend std::istream &operator>>(std::istream &is, Vec3 &v);

private:
  std::array<float, 3> data;
};

Vec3 operator+(const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator-(const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator*(const Vec3 &lhs, const Vec3 &rhs);
Vec3 operator/(const Vec3 &lhs, const Vec3 &rhs);

Vec3 operator*(const Vec3 &lhs, float rhs);
Vec3 operator/(const Vec3 &lhs, float rhs);
Vec3 operator*(float lhs, const Vec3 &rhs);

[[maybe_unused]] float dot(const Vec3 &lhs, const Vec3 &rhs);
[[maybe_unused]] Vec3 cross(const Vec3 &lhs, const Vec3 &rhs);
Vec3 normalize(const Vec3& v);

std::istream &operator>>(std::istream &is, Vec3 &v);
std::ostream &operator<<(std::ostream &os, const Vec3 &v);

}

