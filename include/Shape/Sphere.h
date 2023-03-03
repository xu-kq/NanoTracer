//
// Created by xukq on 22/12/06.
//

#pragma once
#include <Shape/Shape.h>

namespace Tracer {
class Material;
class Sphere : public Shape {
public:
  Sphere() = default;
  Sphere(const Vec3d &center, double radius, std::shared_ptr<Material> p_mat) :
      center{center},
      radius{radius},
      p_mat{std::move(p_mat)} {}

  [[nodiscard]] Intersection Intersect(const Ray &ray) const override;
private:
  Vec3d center{};
  double radius{};
  std::shared_ptr<Material> p_mat;
};

} // Tracer

