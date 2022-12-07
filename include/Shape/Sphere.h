//
// Created by xukq on 22/12/06.
//

#pragma once
#include "Shape.h"

namespace Tracer {

class Sphere : public Shape {
public:
  Sphere() = default;
  Sphere(const Vec3& center, float radius) : center{center}, radius{radius} {}

  [[nodiscard]] Intersection Intersect(const Ray &ray) const override;
private:
	Vec3 center;
	float radius;
};

} // Tracer

