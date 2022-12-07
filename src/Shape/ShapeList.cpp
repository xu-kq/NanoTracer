//
// Created by xukq on 22/12/07.
//

#include <Shape/ShapeList.h>

namespace Tracer {
Intersection ShapeList::Intersect(const Ray &ray) const {
  Intersection ret;
  for(const auto& sphere : spheres) {
	if(Intersection inter = sphere->Intersect(ray); inter) {
		ret =  inter < ret ? inter : ret;
	}
  }
  return ret;
}
} // Tracer