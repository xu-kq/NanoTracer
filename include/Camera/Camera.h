//
// Created by xukq on 22/12/08.
//

#pragma once
#include "Ray/Ray.h"

namespace Tracer {

class Camera {
public:
  Camera(const double width = 32.0 / 9.0, const double height = 2.0, const double focal_length = 1.0) :
      viewport_width{width},
      viewport_height{height},
      aspect_ratio{width / height},
      focal_length{focal_length},
      origin{0, 0, 0},
      horizontal{viewport_width, 0., 0.},
      vertical{0., viewport_height, 0.} {
    lower_left_corner = origin - horizontal / 2. - vertical / 2. - Vec3d{0, 0, focal_length};
  }

  Ray gen_ray(double u, double v) const {
    return {origin, lower_left_corner + u * horizontal + v * vertical - origin};
  }
private:
  double aspect_ratio;
  double viewport_width;
  double viewport_height;
  double focal_length;

  Vec3d origin;
  Vec3d lower_left_corner;
  Vec3d horizontal;
  Vec3d vertical;
};

} // Tracer

