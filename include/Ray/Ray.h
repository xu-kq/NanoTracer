//
// Created by xukq on 22/12/06.
//
#pragma once
#include <math/Vec3.h>

namespace Tracer {

class Ray {
public:
  Ray() {}
  Ray(const Vec3 &orig, const Vec3 &dir, const float t = 0.f) : org{orig}, dir{dir}, t{t} {}

  [[nodiscard]] const Vec3 &origin() const { return org; }
  [[nodiscard]] const Vec3 &direction() const { return dir; }
  Vec3 operator()(float t) const { return org + t * dir; }
private:
  Vec3 org;
  Vec3 dir;
  float t;
};

} // Tracer


