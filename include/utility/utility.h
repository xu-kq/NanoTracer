//
// Created by xukq on 22/12/08.
//

#pragma once
// public common headers
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <BVH/BVH.h>
#include <Camera/Camera.h>
#include <stb_image/stb_image_write.h>
#include <Material/Dielectric.h>
#include <Material/Lambertian.h>
#include <Material/Metal.h>
#include <Ray/Ray.h>
#include <Shape/MovingSphere.h>
#include <Shape/Sphere.h>
#include <Shape/World.h>
#include <Texture/Texture.h>
#include <Texture/CheckerTexture.h>
namespace Tracer {

// constants
extern const double pi;

// utility function
inline Color3 gamma_correction(const Vec3<double> &pixel_color) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  // gamma 2
  r = std::sqrt(r);
  g = std::sqrt(g);
  b = std::sqrt(b);
  return {
      static_cast<int>(256 * std::clamp(r, 0., 0.999)),
      static_cast<int>(256 * std::clamp(g, 0., 0.999)),
      static_cast<int>(256 * std::clamp(b, 0., 0.999))
  };
}

inline double deg2rad(double degrees) { return degrees * pi / 180.; }

int generate_random_int(int min, int max);
double generate_random_double();
double generate_random_double(double min, double max);
Vec3d random_vec3d_in_unit_square();
Vec3d random_vec3d_on_unit_square();
Vec3d random_vec3d_in_hemisphere(const Vec3d &normal);

inline Vec3d reflect(const Vec3d &v, const Vec3d &N) { return v - 2 * dot(v, N) * N; }

} // Tracer

