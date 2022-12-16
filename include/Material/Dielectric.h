//
// Created by xukq on 22/12/15.
//
#pragma once

#include "Material.h"
#include <Shape/Shape.h>

namespace Tracer {

double generate_random_double();
Vec3d random_vec3d_on_unit_square();
Vec3d reflect(const Vec3d &v, const Vec3d &N);

class Dielectric : public Material {
public:
  Dielectric(double index_of_refraction) : ir{index_of_refraction} {}
  std::optional<std::tuple<Vec3d, Ray>> scatter(const Ray &ri, const Intersection &inter) const override {
    double refraction_ratio = inter.front_face ? (1. / ir) : ir;

    Vec3d unit_direction = normalize(ri.direction());
    double cos_theta = std::min(dot(-unit_direction, inter.normal), 1.0);
    double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3d direction;

    if(cannot_refract || reflectance(cos_theta, refraction_ratio) > generate_random_double()) {
      direction = reflect(unit_direction, inter.normal);
    } else {
      direction = refract(unit_direction, inter.normal, refraction_ratio);
    }

    Ray scattered = Ray(inter.coords, direction);
    Vec3d attenuation{1.0, 1.0, 1.0};
    return std::tuple{attenuation, scattered};
  }

private:
  static Vec3d refract(const Vec3d &uv, const Vec3d &n, double etai_over_etat) {
    double cos_theta = std::min(dot(-uv, n), 1.0);
    Vec3d r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Vec3d r_out_parallel = -std::sqrt(std::abs(1.0 - r_out_perp.squared_length()))  * n;
    return r_out_perp + r_out_parallel;
  }
  static double reflectance(double cosine, double ref_idx) {
    // Use schlick's approximation for reflectance.
    auto r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0*r0;
    return r0 + (1 - r0) * std::pow(1 - cosine, 5);
  }
  double ir; // ior
};

} // PT

