//
// Created by xukq on 22/12/06.
//

#pragma once
#include <limits>

#include <Ray/Ray.h>

namespace Tracer {
struct Intersection {
public:
  Intersection() : happened{false}, coords{}, normal{}, distance{std::numeric_limits<float>::max()} {  }

  explicit operator bool() const { return happened; }
  bool operator<(const Intersection &rhs) const { return distance < rhs.distance; }

  bool happened;
  double distance;
  Vec3d coords;
  Vec3d normal;
};

class Shape {
public:
  [[nodiscard]] virtual Intersection Intersect(const Ray &ray) const = 0;
};

} // Tracer

