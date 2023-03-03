//
// Created by xukq on 23/03/03.
//

#pragma once
#include <memory>

#include <Shape/Shape.h>
#include <Shape/World.h>

namespace Tracer {
int generate_random_int(int min, int max);

struct BVH : public Shape {
public:
  BVH() = default;
  BVH(const BVH&) = default;
  BVH(World &w, double time0, double time1)
      : BVH(w.objects(), 0, w.size(), time0, time1) {}
  BVH(std::vector<std::shared_ptr<Shape>> objects,
      std::size_t start, std::size_t end, double time0, double time1);

  Intersection Intersect(const Ray &ray) const override;
  AABB getAABB(double time0, double time1) const override { return box; }
public:
  std::shared_ptr<Shape> left;
  std::shared_ptr<Shape> right;
  AABB box;
  int height;
  static int sz;
};
inline int BVH::sz = 0;

// utility function
bool box_compare(const std::shared_ptr<Shape> lhs, const std::shared_ptr<Shape> rhs, int axis);
bool box_x_compare(const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);
bool box_y_compare(const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);
bool box_z_compare(const std::shared_ptr<Shape>, const std::shared_ptr<Shape>);
} // Tracer

