//
// Created by xukq on 22/12/08.
//

#pragma once
#include "Ray/Ray.h"

namespace Tracer {

class Camera {
public:
  Camera(Vec3d lookfrom, Vec3d lookat, Vec3d vup, const double vfov, const double aspect_ratio)
      : origin{lookfrom} {
    constexpr double focal_length = 1.0;
    double viewport_height = 2 * focal_length * std::tan(vfov / 2);
    double viewport_width = aspect_ratio * viewport_height;

    auto w = normalize(lookfrom - lookat);
    auto u = normalize(cross(vup, w));
    auto v = cross(w, u);

    horizontal = viewport_width * u;
    vertical = viewport_height * v;
    lower_left_corner = origin - horizontal / 2. - vertical / 2. - w;
  }

  Ray gen_ray(double u, double v) const {
    return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
  }
private:
  Vec3d origin;
  Vec3d lower_left_corner;
  Vec3d horizontal;
  Vec3d vertical;
};

} // Tracer

