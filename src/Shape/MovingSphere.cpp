//
// Created by xukq on 23/03/03.
//

#include <Shape/MovingSphere.h>

namespace Tracer {
Intersection MovingSphere::Intersect(const Ray &ray) const {
  Intersection inter;
  double _time = ray.time();
  Vec3 oc = ray.origin() - center(_time) ;
  double a = dot(ray.direction(), ray.direction());
  double b = 2. * dot(oc, ray.direction());
  double c = dot(oc, oc) - radius * radius;

  if(double det = b * b - 4 * a * c; det > 0) {
    constexpr double tol = 1e-10;
    if(double x1 = ((-b - std::sqrt(det)) / (2. * a)); x1 > tol) {
      inter.happened = true;
      inter.distance = x1;
      inter.coords = ray(x1);
      inter.normal = (inter.coords - center(_time)) / radius;
      inter.p_mat = pMat;

      Vec3d outward_normal = (inter.coords - center(_time)) / radius;
      inter.set_face_normal(ray, outward_normal);
    }
    else if(double x2 = ((-b + std::sqrt(det)) / (2. * a)); x2 > tol) {
      inter.happened = true;
      inter.distance = x2;
      inter.coords = ray(x2);
      inter.normal = (inter.coords - center(_time)) / radius;
      inter.p_mat = pMat;

      Vec3d outward_normal = (inter.coords - center(_time)) / radius;
      inter.set_face_normal(ray, outward_normal);
    }
  }
  return inter;
}
Vec3d MovingSphere::center(double time) const {
  Vec3d ret = center0 + (time - time0) / (time1 - time0) * (center1 - center0);
  return ret;
}
}  // Tracer
