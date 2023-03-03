//
// Created by xukq on 23/03/03.
//

#include <BVH/BVH.h>
#include <functional>
#include <array>
#include <algorithm>

namespace Tracer {
Intersection BVH::Intersect(const Ray &ray) const {
  Intersection inter;
  if (!box.hit(ray)) {
    return inter;
  }
  Intersection lhs = left->Intersect(ray);
  Intersection rhs = right->Intersect(ray);
  inter = lhs < rhs ? lhs : rhs;
  return inter;
}

BVH::BVH(std::vector<std::shared_ptr<Shape>> objects,
         std::size_t start,
         std::size_t end,
         double time0,
         double time1) {
  int axis = generate_random_int(0, 2);
  using cps = const std::shared_ptr<Shape>;
  static std::array<std::function<bool(cps, cps)>, 3> func
      {
          box_x_compare,
          box_y_compare,
          box_z_compare
      };
  auto comparator = func[axis];
  std::size_t object_span = end - start;

  if (object_span == 1) {
    height = 0;
    sz += 1;
    left = objects[start];
    right = objects[start];
  } else if (object_span == 2) {
    height = 0;
    sz+=2;
    if (comparator(objects[start], objects[start + 1])) {
      left = objects[start];
      right = objects[start + 1];
    } else {
      left = objects[start + 1];
      right = objects[start];
    }
  } else {
    std::sort(objects.begin() + start, objects.begin() + end, comparator);

    auto mid = start + object_span / 2;
    auto temp_left = std::make_shared<BVH>(objects, start, mid, time0, time1);
    auto temp_right =std::make_shared<BVH>(objects, mid, end, time0, time1);
    left = temp_left;
    right = temp_right;
    height = std::max(temp_left->height, temp_right->height) + 1;
  }

  AABB boxLeft = left->getAABB(time0, time1);
  AABB boxRight = right->getAABB(time0, time1);
  box = Union(boxLeft, boxRight);
}

bool box_compare(const std::shared_ptr<Shape> lhs, const std::shared_ptr<Shape> rhs, int axis) {
  AABB boxLhs = lhs->getAABB(0, 0);
  AABB boxRhs = rhs->getAABB(0, 0);
  return boxLhs.min()[axis] < boxRhs.min()[axis];
}
bool box_x_compare(const std::shared_ptr<Shape> lhs, const std::shared_ptr<Shape> rhs) {
  return box_compare(lhs, rhs, 0);
}
bool box_y_compare(const std::shared_ptr<Shape> lhs, const std::shared_ptr<Shape> rhs) {
  return box_compare(lhs, rhs, 1);
}
bool box_z_compare(const std::shared_ptr<Shape> lhs, const std::shared_ptr<Shape> rhs) {
  return box_compare(lhs, rhs, 2);
}
} // Tracer