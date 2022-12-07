//
// Created by xukq on 22/12/06.
//

#pragma once
#include <limits>

#include <Ray/Ray.h>

namespace Tracer {
struct Intersection {
  Intersection() : happened{false}, coords{}, normal{}, distance{std::numeric_limits<float>::max()} {}
  explicit operator bool() const { return happened; }
  bool operator<(const Intersection &rhs) const { return distance < rhs.distance; }

  bool happened;
  [[maybe_unused]] float distance;
  [[maybe_unused]] Vec3 coords;
  [[maybe_unused]] Vec3 normal;
};

class Shape {
public:
  [[maybe_unused, nodiscard]] virtual Intersection Intersect(const Ray &ray) const = 0;
};

} // Tracer

