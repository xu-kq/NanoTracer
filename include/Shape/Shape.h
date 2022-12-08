//
// Created by xukq on 22/12/06.
//

#pragma once
#include <limits>
#include <memory>

#include <Ray/Ray.h>

namespace Tracer {

class Material;
struct Intersection {
public:
  Intersection() :
      happened{false},
      coords{},
      normal{},
      distance{std::numeric_limits<float>::max()},
      front_face{} {}

  explicit operator bool() const { return happened; }
  bool operator<(const Intersection &rhs) const { return distance < rhs.distance; }

  void set_face_normal(const Ray &r, const Vec3d &outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }

  bool happened;
  double distance;
  Vec3d coords;
  Vec3d normal;
  std::shared_ptr<Material> p_mat;
  bool front_face;
};

class Shape {
public:
  [[nodiscard]] virtual Intersection Intersect(const Ray &ray) const = 0;
};

} // Tracer

