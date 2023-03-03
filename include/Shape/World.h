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
  [[maybe_unused]] explicit World(const std::vector<std::shared_ptr<Shape>> &shapes) : shapes{shapes} {}

  [[nodiscard]] Intersection Intersect(const Ray &ray) const override;
  AABB getAABB(double time0, double time1) const override;

  void push(std::shared_ptr<Shape> ps) { shapes.push_back(ps); }
  std::size_t size() const {
    return shapes.size();
  }
  const auto& objects() const {
    return shapes;
  }
private:
  std::vector<std::shared_ptr<Shape>> shapes;
};

} // Tracer

