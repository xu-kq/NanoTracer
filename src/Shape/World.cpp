//
// Created by xukq on 22/12/07.
//

#include <Shape/World.h>

namespace Tracer {
Intersection World::Intersect(const Ray &ray) const {
  Intersection ret;
  for(const auto& sphere : spheres) {
    if (Intersection inter = sphere->Intersect(ray); inter) {
      ret = inter < ret ? inter : ret;
    }
  }
  return ret;
}
} // Tracer