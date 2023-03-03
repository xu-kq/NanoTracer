//
// Created by xukq on 23/03/03.
//

#pragma once
#include <math/Vec3.hpp>
#include <Ray/Ray.h>

namespace Tracer {

class AABB {
public:
  AABB() = default;
  AABB(const Vec3d &a, const Vec3d &b) : minimum{a}, maximum{b} {}

  Vec3d min() const { return minimum; }
  Vec3d max() const { return maximum; }

  bool hit(const Ray &ray) const;

private:
  Vec3d minimum;
  Vec3d maximum;
};

AABB Union(AABB lhs, AABB rhs);
} // Tracer

