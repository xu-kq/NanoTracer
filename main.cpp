//
// Created by xukq on 22/12/07.
//

#include <utility/utility.h>

namespace Tracer {

Vec3d cast_ray(const Ray &r, const World &world, int depth) {
  if (depth <= 0) {
    return {0, 0, 0};
  }

  if (Intersection inter = world.Intersect(r); inter) {
    if (auto ret = inter.p_mat->scatter(r, inter); ret) {
      auto [attenuation, scattered] = ret.value();
      return attenuation * cast_ray(scattered, world, depth - 1);
    } else {
      return {0, 0, 0};
    }
  } else {
    Vec3d u_dir = normalize(r.direction());
    double t = 0.5 * (u_dir.y() + 1.);
    return (1 - t) * Vec3d{1, 1, 1} + t * Vec3d{0.5, 0.7, 1.0};
  }
}

} // Tracer

int main() {

  // Image
  constexpr int width = 1960;
  constexpr int height = 1080;
  constexpr int channel = 4;
  [[maybe_unused]] constexpr double aspect_ratio = static_cast<double>(width) / height;
  constexpr double focal_length = 600;

  std::string filename = "image.png";
  std::vector<char> data(width * width * channel);


  // Material
  auto m_gouraud = std::make_shared<Tracer::Lambertian>(Tracer::Vec3d{0.8, 0.8, 0.0});
  auto m_center = std::make_shared<Tracer::Lambertian>(Tracer::Vec3d{0.1, 0.2, 0.5});
  auto m_left = std::make_shared<Tracer::Dielectric>(1.5);
  auto m_right = std::make_shared<Tracer::Metal>(Tracer::Vec3d{0.8, 0.6, 0.2}, 0.0);

  // World
  Tracer::World world;

  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0., -100.5, -1}, 100., m_gouraud));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0, 0, -1}, 0.5, m_center));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{-1, 0, -1}, 0.5, m_left));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{-1, 0, -1}, -0.45, m_left));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{1, 0, -1}, 0.5, m_right));

  // Camera
  Tracer::Vec3d lookfrom{3,3,2};
  Tracer::Vec3d lookat{0,0,-1};
  Tracer::Vec3d vup{0,1,0};
  auto dist_to_focus = (lookfrom - lookat).length();
  auto aperture = 2.0;
  double fov = 20.;
  fov = Tracer::deg2rad(fov);
  Tracer::Camera
      camera{lookfrom, lookat, vup, fov, aspect_ratio, aperture, dist_to_focus};

  // Render loop
  constexpr int max_depth = 50;
  constexpr int samples_per_pixel = 100;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      Tracer::Color3 col;
      for (int sp = 0; sp < samples_per_pixel; ++sp) {
        double u = (i + Tracer::generate_random_double()) / width;
        double v = (j + Tracer::generate_random_double()) / height;
        Tracer::Ray ray = camera.gen_ray(u, v);
        col += gamma_correction(Tracer::cast_ray(ray, world, max_depth));
      }
      col /= samples_per_pixel;

      data[j * width * channel + i * channel + 0] = static_cast<char>(col.x());
      data[j * width * channel + i * channel + 1] = static_cast<char>(col.y());
      data[j * width * channel + i * channel + 2] = static_cast<char>(col.z());
      data[j * width * channel + i * channel + 3] = static_cast<char>(255);
    }
  }
  stbi_flip_vertically_on_write(true);
  stbi_write_png(filename.c_str(), width, height, channel, data.data(), 0);
}


