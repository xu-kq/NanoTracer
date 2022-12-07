//
// Created by xukq on 22/12/07.
//

#pragma once
#include <vector>
#include "Sphere.h"

namespace Tracer {

class ShapeList : public Sphere {
public:
  ShapeList() = default;
  [[maybe_unused]] explicit ShapeList(const std::vector<std::shared_ptr<Sphere>> &spheres) : spheres{spheres} {}

  [[nodiscard]] Intersection Intersect(const Ray &ray) const override;
  void push(std::shared_ptr<Sphere> ps) { spheres.push_back(ps); }
private:
  std::vector<std::shared_ptr<Sphere>> spheres;
};

} // Tracer

