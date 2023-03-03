//
// Created by xukq on 23/03/03.
//

#include <AABB/AABB.h>

namespace Tracer {
bool AABB::hit(const Ray &ray) const {
  for (int i = 0; i < 3; ++i) {
    auto invD = 1. / ray.direction()[i];
    auto tMin = std::min((minimum[i] - ray.origin()[i]) * invD,
                         (maximum[i] - ray.origin()[i]) * invD);
    auto tMax = std::max((minimum[i] - ray.origin()[i]) * invD,
                         (maximum[i] - ray.origin()[i]) * invD);
    if (tMax < 0 || tMax < tMin) {
      return false;
    }
  }
  return true;
}

AABB Union(AABB lhs, AABB rhs) {
  Vec3d minimum{
      std::min(lhs.min().x(), rhs.min().x()),
      std::min(lhs.min().y(), rhs.min().y()),
      std::min(lhs.min().z(), rhs.min().z())
  };
  Vec3d maximum{
      std::max(lhs.max().x(), rhs.max().x()),
      std::max(lhs.max().y(), rhs.max().y()),
      std::max(lhs.max().z(), rhs.max().z())
  };
  AABB ret{minimum, maximum};
  return ret;
}

} // Tracer