//
// Created by xukq on 22/12/08.
//

#pragma once
#include "Material.h"
#include <Shape/Shape.h>

namespace Tracer {

Vec3d random_vec3d_in_unit_square();
Vec3d reflect(const Vec3d &v, const Vec3d &N);

class Metal : public Material {
public:
  explicit Metal(const Vec3d &albedo, double fuzzy) : albedo{albedo}, fuzzy{fuzzy < 1.0 ? fuzzy : fuzzy} {}

  virtual std::optional<std::tuple<Vec3d, Ray>> scatter(const Ray &ri, const Intersection &inter) const override {
    Vec3d reflected = reflect(normalize(ri.direction()), inter.normal);
    Ray scattered = {inter.coords, reflected + fuzzy * random_vec3d_in_unit_square(), ri.time()};
    Vec3d attenuation = albedo;
    if (dot(scattered.direction(), inter.normal) > 0) {
      return std::tuple{attenuation, scattered};
    } else {
      return std::nullopt;
    }
  }

private:
  Vec3d albedo;
  double fuzzy;
};

} // Tracer
