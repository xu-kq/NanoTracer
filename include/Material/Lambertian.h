//
// Created by xukq on 22/12/08.
//

#pragma once
#include "Material.h"

#include <Shape/Shape.h>

namespace Tracer {

Vec3d random_vec3d_on_unit_square();
class Lambertian : public Material {
public:
  explicit Lambertian(const Vec3d &albedo) : albedo{albedo} {}
  [[nodiscard]] std::optional<std::tuple<Vec3d, Ray>> scatter(const Ray &ri, const Intersection &inter) const override {
    auto scatter_direction = inter.normal + random_vec3d_on_unit_square();

    // discarding all near grazing angle, and return a normal direction.
    if (scatter_direction.near_zero()) {
      scatter_direction = inter.normal;
    }
    Ray scattered = {inter.coords, scatter_direction, ri.time()};
    Vec3d attenuation = albedo;
    return std::tuple{attenuation, scattered};
  }

private:
  Vec3d albedo;
};

}// namespace Tracer
