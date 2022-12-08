//
// Created by xukq on 22/12/08.
//

#pragma once
#include <optional>
#include <tuple>

#include <Ray/Ray.h>

namespace Tracer {

struct Intersection;
class Material {
public:
  virtual std::optional<std::tuple<Vec3d, Ray>> scatter(const Ray &ri, const Intersection &inter) const = 0;
};

} // Tracer

