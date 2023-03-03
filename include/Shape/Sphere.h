//
// Created by xukq on 22/12/06.
//

#pragma once
#include <Shape/Shape.h>

namespace Tracer {
class Material;
extern const double pi;
class Sphere : public Shape {
public:
  Sphere() = default;
  Sphere(const Vec3d &center, double radius, std::shared_ptr<Material> p_mat) :
      center{center},
      radius{radius},
      p_mat{std::move(p_mat)} {}

  Intersection Intersect(const Ray &ray) const override;
  AABB getAABB(double time0, double time1) const override;

private:
  static void get_sphere_uv(const Vec3d &p, double &u, double &v) {

    auto theta = std::acos(-p.y());
    auto phi = std::atan2(-p.z(), p.x()) + pi;

    u = phi / (2 * pi);
    v = theta / pi;
  }

private:
  Vec3d center{};
  double radius{};
  std::shared_ptr<Material> p_mat;
};

} // Tracer

