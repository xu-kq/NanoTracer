//
// Created by xukq on 22/12/07.
//

#include <utility/utility.h>

namespace Tracer {
Vec3d cast_ray(const Ray &r, const World &world, int depth);
World random_scene();
}

int main() {

  constexpr int max_depth = 50;
  constexpr int samples_per_pixel = 50;

  // Image
  constexpr int width = 800;
  constexpr int height = 600;
  constexpr int channel = 4;
  constexpr double aspect_ratio = static_cast<double>(width) / height;

//  std::string filename = "../../image/Default.png";
  std::string filename = "../../image/MotionBlur_800x600_50spp.png";
  std::vector<char> data(width * width * channel);


  // World
  Tracer::World world = Tracer::random_scene();


  // Camera
  Tracer::Vec3d lookfrom{13, 2, 3};
  Tracer::Vec3d lookat{0, 0, 0};
  Tracer::Vec3d vup{0, 1, 0};
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;
  double fov = 20.;
  fov = Tracer::deg2rad(fov);
  Tracer::Camera
      camera{lookfrom, lookat, vup, fov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0};

  // Render loop
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

World random_scene() {
  World world;

  auto gouraud_material = std::make_shared<Lambertian>(Vec3d{0.5, 0.5, 0.5});
  world.push(std::make_shared<Sphere>(Vec3d{0, -1000, 0}, 1000, gouraud_material));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      auto choose_mat = generate_random_double();
      Vec3d center{a + 0.9 * generate_random_double(), 0.2, b + 0.9 * generate_random_double()};

      if ((center - Vec3d{4, 0.2, 0}).length() > 0.9) {
        std::shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto color_random = [&]() -> Vec3d {
            return {generate_random_double(), generate_random_double(), generate_random_double()};
          };
          auto albedo = color_random() * color_random();
          sphere_material = std::make_shared<Lambertian>(albedo);
          auto center2 = center + Vec3d{0., generate_random_double(0, .5), 0.};
          world.push(std::make_shared<MovingSphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto color_random = [&](double min, double max) -> Vec3d {
            return {
                generate_random_double(min, max),
                generate_random_double(min, max),
                generate_random_double(min, max)
            };
          };
          auto albedo = color_random(0.5, 1);
          auto fuzz = generate_random_double(0, 0.5);
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.push(std::make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<Dielectric>(1.5);
          world.push(std::make_shared<Sphere>(center, 0.2, sphere_material));
      }
    }
  }
}

  auto material1 = std::make_shared<Dielectric>(1.5);
  world.push(std::make_shared<Sphere>(Vec3d{0,1,0}, 1, material1));

  auto material2 = std::make_shared<Lambertian>(Vec3d{0.4, 0.2, 0.1});
  world.push(std::make_shared<Sphere>(Vec3d{-4,1,0}, 1, material2));

  auto material3 = std::make_shared<Metal>(Vec3d{0.7, 0.6, 0.6}, 0.0);
  world.push(std::make_shared<Sphere>(Vec3d{4,1,0}, 1, material3));

  return world;
}

} // Tracer