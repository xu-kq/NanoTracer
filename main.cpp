//
// Created by xukq on 22/12/07.
//

#include <utility/utility.h>


namespace Tracer {

Color3 visualization_normal_vector(const Ray &r, const World &world) {
  if (Intersection inter = world.Intersect(r); inter) {
	Vec3d N = inter.normal;
	return scale_to_color(
		0.5 * (N + Vec3d{1, 1, 1})
	);
  } else {
	Vec3d u_dir = normalize(r.direction());
	double t = 0.5 * (u_dir.y() + 1.f);
	return scale_to_color(
		(1 - t) * Vec3d{1, 1, 1} + t * Vec3d{0.5, 0.7, 1.0}
	);
  }
}

} // Tracer

int main() {
  constexpr int width = 1960;
  constexpr int height = 1080;

  float aspect_ratio = static_cast<float>(width) / height;
  Tracer::Vec3d lower_left_corner{-2., -1., -1.};
  Tracer::Vec3d horizontal{4., 0., 0.};
  Tracer::Vec3d vertical{0., 4.f / aspect_ratio, 0.};
  Tracer::Vec3d origin{0., 0., 0.};

  constexpr int comp = 4;
  std::string filename = "image.png";
  std::vector<char> data(width * height * comp);

  Tracer::World world;
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0, 0, -1}, 0.5));
  world.push(std::make_shared<Tracer::Sphere>(Tracer::Vec3d{0, -100.5, -1}, 100));

  // Visualization for Y Coordinate
  for (int j = 0; j < height; ++j) {
	for (int i = 0; i < width; ++i) {
	  double u = static_cast<double>(i) / width;
	  double v = static_cast<double>(j) / height;

	  Tracer::Ray ray{origin, lower_left_corner + u * horizontal + v * vertical};
	  Tracer::Color3 col = Tracer::visualization_normal_vector(ray, world);

	  data[j * width * comp + i * comp + 0] = static_cast<char>(col.x());
	  data[j * width * comp + i * comp + 1] = static_cast<char>(col.y());
	  data[j * width * comp + i * comp + 2] = static_cast<char>(col.z());
	  data[j * width * comp + i * comp + 3] = static_cast<char>(255);
	}
  }
  stbi_flip_vertically_on_write(true);
  stbi_write_png(filename.c_str(), width, height, comp, data.data(), 0);
}


