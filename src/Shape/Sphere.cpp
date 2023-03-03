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
    constexpr double tol = 1e-10;
	if(double x1 = ((-b - std::sqrt(det)) / (2. * a)); x1 > tol) {
	  inter.happened = true;
	  inter.distance = x1;
	  inter.coords = ray(x1);
	  inter.normal = (inter.coords - center) / radius;
	  inter.p_mat = p_mat;

    Vec3d outward_normal = (inter.coords - center) / radius;
    inter.set_face_normal(ray, outward_normal);
	}
	else if(double x2 = ((-b + std::sqrt(det)) / (2.f * a)); x2 > tol) {
	  inter.happened = true;
	  inter.distance = x2;
	  inter.coords = ray(x2);
	  inter.normal = (inter.coords - center) / radius;
	  inter.p_mat = p_mat;

    Vec3d outward_normal = (inter.coords - center) / radius;
    inter.set_face_normal(ray, outward_normal);
    get_sphere_uv(outward_normal, inter.u, inter.v);
	}
  }
	return inter;
}

AABB Sphere::getAABB(double time0, double time1) const {
  auto ret = AABB{
      center - Vec3d{radius, radius, radius},
      center + Vec3d{radius, radius, radius}
  };
  return ret;
}
} // Tracer