#include <iostream>
#include <vector>
#include <filesystem>
#include "stb_image/stb_image_write.h"

class create_directories;
int main(int argc, char* argv[]) {


  int nx = 200;
  int ny = 100;

  std::string filename = "image.png";
  int w{nx},
	  h{ny},
	  comp{4};

  std::vector<char> data(w * h * comp);
  for(int j = 0; j < ny; j++) {
	for(int i = 0; i < nx; i++) {
	  float r = float(i) / float(nx);
	  float g = float(j) / float(ny);
	  float b = 0.2;
	  float a = 1.0;

	  int ir = static_cast<int>(255.99 * r);
	  int ig = static_cast<int>(255.99 * g);
	  int ib = static_cast<int>(255.99 * b);
	  int ia = static_cast<int>(255.99 * a);

	  data[j * nx * comp + i * comp + 0] = static_cast<char>(ir);
	  data[j * nx * comp + i * comp + 1] = static_cast<char>(ig);
	  data[j * nx * comp + i * comp + 2] = static_cast<char>(ib);
	  data[i * ny * comp + j * comp + 3] = static_cast<char>(ia);
	}
  }
  std::cout << argv[0] << std::endl;
  stbi_flip_vertically_on_write(true);
  stbi_write_png(filename.c_str(), w, h, comp, data.data(), 0);
}
