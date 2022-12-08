//
// Created by xukq on 22/12/08.
//

#include "utility/utility.h"

namespace Tracer {

double generate_random_double()  {
  static std::random_device seed;
  static std::mt19937_64 engine(seed());
  static std::uniform_real_distribution uniform_dist(0.0, 1.0);
  return uniform_dist(engine);
}
double generate_random_double(double min, double max) {
  static std::random_device seed;
  static std::mt19937_64 engine(seed());
  static std::uniform_real_distribution uniform_dist(min, max);
  return uniform_dist(engine);
}
Vec3d random_vec3d_in_unit_square() {
  // reject sampling
  auto gen = [] () {
	return generate_random_double();
  };
  Vec3d ret;
  do {
	ret = {gen(), gen(), gen() };
  } while(ret.squared_length() > 1);
  return ret;
}
Vec3d random_vec3d_in_unit_square(double min, double max) {
  // reject sampling
  auto gen = [&] () {
	return generate_random_double(min, max);
  };
  Vec3d ret;
  do {
	ret = {gen(), gen(), gen() };
  } while(ret.squared_length() > 1);
  return ret;
}
Vec3d random_vec3d_on_unit_square() {
  return random_vec3d_in_unit_square().normalized();
}
Vec3d random_vec3d_in_hemisphere(const Vec3d &normal) {
  Vec3d in_unit_sphere = random_vec3d_in_unit_square();
  if(dot(in_unit_sphere, normal) > 0.)
	return in_unit_sphere;
  else
	return -in_unit_sphere;
}
} // Tracer