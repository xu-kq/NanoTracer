//
// Created by xukq on 23/03/03.
//

#pragma once
#include <Shape/Shape.h>
#include <math/Vec3.hpp>

namespace Tracer {
class Material;

class MovingSphere : public Shape {
public:
  MovingSphere() = default;
  MovingSphere(
      Vec3d cen0, Vec3d cen1, double _time0, double _time1, double r, std::shared_ptr<Material> pm)
      : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), pMat(pm) {}

  Intersection Intersect(const Ray &ray) const override;
  Vec3d center(double time) const;

private:
  Vec3d center0, center1;
  double time0, time1;
  double radius;
  std::shared_ptr<Material> pMat;
};
}  // Tracer
