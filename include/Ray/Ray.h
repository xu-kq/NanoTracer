//
// Created by xukq on 22/12/06.
//
#pragma once
#include <math/Vec3.hpp>

namespace Tracer {

class Ray {
public:
  Ray() = default;
  Ray(const Vec3d &orig, const Vec3d &dir, const double t = 0.f) : org{orig}, dir{dir}, t{t} {}

  [[nodiscard]] const Vec3d &origin() const { return org; }
  [[nodiscard]] const Vec3d &direction() const { return dir; }
  double time() const {return t; }

  Vec3d operator()(double coef) const { return org + coef * dir; }
private:
  Vec3d org;
  Vec3d dir;
  double t;
};

} // Tracer


