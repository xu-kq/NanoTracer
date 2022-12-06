#include <iostream>
#include "stb_image/stb_image_write.h"
#include "Ray/Ray.h"

Tracer::Vec3 color(const Tracer::Ray &r) {
  using Tracer::Vec3, Tracer::Ray;
  Vec3 u_dir = normalize(r.direction());
  float t = 0.5f * (u_dir.y() + 1.f);
  return (1.f - t) * Vec3{1.f, 1.f, 1.f} + t * Vec3{0.5, 0.7, 1.0};
}

int main() {
  constexpr int width = 200;
  constexpr int height = 100;
  Tracer::Vec3 lower_left_corner{-2., -1., -1.};
  Tracer::Vec3 horizontal{4., 0., 0.};
  Tracer::Vec3 vertical{0., 2., 0.};
  Tracer::Vec3 origin{0., 0., 0.};

  constexpr int comp = 4;
  std::string filename = "image.png";
  std::array<char, width * height * comp> data{};
  // Visualization for Y Coordinate
  for (int j = 0; j < height; ++j) {
	for (int i = 0; i < width; ++i) {
	  float u = static_cast<float>(i) / width;
	  float v = static_cast<float>(j) / height;

	  Tracer::Ray ray{origin, lower_left_corner + u * horizontal + v * vertical};
	  Tracer::Vec3 col = color(ray);

	  int ir = static_cast<int>(255.99 * col[0]);
	  int ig = static_cast<int>(255.99 * col[1]);
	  int ib = static_cast<int>(255.99 * col[2]);
	  int ia = static_cast<int>(255.99 * 1);

	  data[j * width * comp + i * comp + 0] = static_cast<char>(ir);
	  data[j * width * comp + i * comp + 1] = static_cast<char>(ig);
	  data[j * width * comp + i * comp + 2] = static_cast<char>(ib);
	  data[j * width * comp + i * comp + 3] = static_cast<char>(ia);
	}
  }
  stbi_flip_vertically_on_write(true);
  stbi_write_png(filename.c_str(), width, height, comp, data.data(), 0);
}
