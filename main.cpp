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
	Vec3d target = inter.coords + inter.normal + random_vec3d_in_unit_square();
	return 0.5 * cast_ray({inter.coords, target - inter.coords}, world, depth - 1);
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

  std::string filename = "anti-aliasing.png";
  std::vector<char> data(width * width * channel);


  // World
  Tracer::World world;
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0, 0, -1}, 0.5));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0, -100.5, -1}, 100));

  // Camera
  Tracer::Camera camera{width, height, focal_length};

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
		col += scale_to_color(Tracer::cast_ray(ray, world, max_depth));
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


