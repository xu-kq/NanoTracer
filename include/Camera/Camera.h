//
// Created by xukq on 22/12/08.
//

#pragma once
#include "Ray/Ray.h"

namespace Tracer {

Vec3d random_vec3d_in_unit_square();

class Camera {
public:
  Camera(Vec3d lookfrom,
         Vec3d lookat,
         Vec3d vup,
         const double vfov,
         const double aspect_ratio,
         double aperture,
         double focus_dist)
      : origin{lookfrom},
        lens_radius{aperture / 2} {
    double viewport_height = 2 * std::tan(vfov / 2);
    double viewport_width = aspect_ratio * viewport_height;

    w = normalize(lookfrom - lookat);
    u = normalize(cross(vup, w));
    v = cross(w, u);

    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2. - vertical / 2. - focus_dist * w;
  }

  Ray gen_ray(double s, double t) const {
    Vec3d rd = lens_radius * random_vec3d_in_unit_square();
    Vec3d offset = rd.x() * u + rd.y() * v;

    return {
        origin + offset,
        lower_left_corner + s * horizontal + t * vertical - origin - offset
    };
  }
private:
  Vec3d origin;
  Vec3d lower_left_corner;
  Vec3d horizontal;
  Vec3d vertical;

  Vec3d u;
  Vec3d v;
  Vec3d w;
  double lens_radius;
};

} // Tracer

