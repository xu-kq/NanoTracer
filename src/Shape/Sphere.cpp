//
// Created by xukq on 22/12/06.
//

#include <Shape/Sphere.h>

namespace Tracer {
Intersection Sphere::Intersect(const Ray &ray) const {
  Intersection inter;
  Vec3 oc = ray.origin() - center;
  double a = dot(ray.direction(), ray.direction());
  double b = 2. * dot(oc, ray.direction());
  double c = dot(oc, oc) - radius * radius;

  if(double det = b * b - 4 * a * c; det > 0) {
	if(double x1 = ((-b - std::sqrt(det)) / (2. * a)); x1 > 0) {
	  inter.happened = true;
	  inter.distance = x1;
	  inter.coords = ray(x1);
	  inter.normal = (inter.coords - center) / radius;
	}
	else if(double x2 = ((-b + std::sqrt(det)) / (2.f * a)); x2 > 0) {
	  inter.happened = true;
	  inter.distance = x2;
	  inter.coords = ray(x2);
	  inter.normal = (inter.coords - center) / radius;
	}
  }
	return inter;
}
} // Tracer