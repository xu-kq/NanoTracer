//
// Created by xukq on 22/12/07.
//

#pragma once
#include "Shape.h"
#include <vector>

namespace Tracer {

class World : public Shape {
public:
  World() = default;
  [[maybe_unused]] explicit World(const std::vector<std::shared_ptr<Shape>> &spheres) : spheres{spheres} {}

  [[nodiscard]] Intersection Intersect(const Ray &ray) const override;
  void push(std::shared_ptr<Shape> ps) { spheres.push_back(ps); }
private:
  std::vector<std::shared_ptr<Shape>> spheres;
};

} // Tracer

