//
// Created by xukq on 23/03/03.
//

#pragma once

#include <math/Vec3.hpp>
namespace Tracer {

class Texture {
public:
  virtual Vec3d value(double u, double v, const Vec3d& p) const = 0;
};

class SolidColor : public Texture {
public:
  SolidColor() = default;
  SolidColor(Vec3d c) : color_value{c} {}
  SolidColor(double red, double green, double blue) : color_value{red, green, blue} {}

  virtual Vec3d value(double u, double v, const Vec3d& p) const override {
    return color_value;
  }
private:
  Vec3d color_value;
};

} // Tracer

