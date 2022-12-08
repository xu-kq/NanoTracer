//
// Created by xukq on 22/12/08.
//

#pragma once
// public common headers
#include <algorithm>
#include <array>
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


#include <Camera/Camera.h>
#include <math/Vec3.hpp>
#include <Ray/Ray.h>
#include <Shape/Shape.h>
#include <Shape/Sphere.h>
#include <Shape/World.h>
#include <stb_image/stb_image_write.h>

namespace Tracer {

// constants
constexpr long double pi{3.14159265358979329l};

// utility function
inline Color3 scale_to_color(const Vec3<double> &pixel_color) {
  return {
	  static_cast<int>(255.999 * pixel_color[0]),
	  static_cast<int>(255.999 * pixel_color[1]),
	  static_cast<int>(255.999 * pixel_color[2])
  };
}

inline double deg2rad(double degrees) { return degrees * pi / 180.; }

double generate_random_double();
double generate_random_double(double min, double max);
Vec3d random_vec3d_in_unit_square();

} // Tracer

