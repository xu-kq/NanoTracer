//
// Created by xukq on 23/03/03.
//

#pragma once
#include <Texture/Texture.h>

namespace Tracer {

class CheckerTexture : public Texture {
public:
  CheckerTexture() = default;
  CheckerTexture(std::shared_ptr<Texture> _even, std::shared_ptr<Texture> _odd)
      : even{_even}, odd{_odd} {}
  CheckerTexture(Vec3d c1, Vec3d c2)
      : even{std::make_shared<SolidColor>(c1)}, odd{std::make_shared<SolidColor>(c2)} {}

  virtual Vec3d value(double u, double v, const Vec3d &p) const override {
    auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
    if (sines < 0) {
      return odd->value(u, v, p);
    } else {
      return even->value(u, v, p);
    }
  }
private:
  std::shared_ptr<Texture> odd;
  std::shared_ptr<Texture> even;
};

}// Tracer
