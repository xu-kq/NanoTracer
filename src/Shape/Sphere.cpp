//
// Created by xukq on 22/12/06.
//

#include <Shape/Sphere.h>

namespace Tracer {
Intersection Sphere::Intersect(const Ray &ray) const {
  Intersection inter;
  Vec3 oc = ray.origin() - center;
  float a = dot(ray.direction(), ray.direction());
  float b = 2.f * dot(oc, ray.direction());
  float c = dot(oc, oc) - radius * radius;

  if(float det = b * b - 4 * a * c; det > 0) {
	if(float x1 = ((-b - std::sqrt(det)) / (2.f * a)); x1 > 0) {
	  inter.happened = true;
	  inter.distance = x1;
	  inter.coords = ray(x1);
	  inter.normal = (inter.coords - center) / radius;
	  return inter;
	}
	else if(float x2 = ((-b + std::sqrt(det)) / (2.f * a)); x2 > 0) {
	  inter.happened = true;
	  inter.distance = x2;
	  inter.coords = ray(x2);
	  inter.normal = (inter.coords - center) / radius;
	  return inter;
	}
	else {
		return inter;
	}
  }
  else {
	return inter;
  }
}
} // Tracer