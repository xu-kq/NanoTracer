//
// Created by xukq on 22/12/07.
//

#include <Shape/World.h>
#include <AABB/AABB.h>

namespace Tracer {
Intersection World::Intersect(const Ray &ray) const {
  Intersection ret;
  for(const auto& shape : shapes) {
    if (Intersection inter = shape->Intersect(ray); inter) {
      ret = inter < ret ? inter : ret;
    }
  }
  return ret;
}
AABB World::getAABB(double time0, double time1) const {
  AABB ret;
  for(const auto& shape : shapes) {
    ret = Union(ret, shape->getAABB(time0, time1));
  }
  return ret;
}
} // Tracer