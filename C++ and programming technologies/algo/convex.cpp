#include <iostream>
#include <vector>

class Geometry {
 public:
  struct Point {
    int64_t x = 0;
    int64_t y = 0;
  };

  struct Vector {
    int64_t x = 0;
    int64_t y = 0;

    Vector(int64_t x, int64_t y) : x(x), y(y) {
    }

    Vector(Point a, Point b) {
      x = b.x - a.x;
      y = b.y - a.y;
    }
  };

  static int64_t VectorProduct(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
  }
};

int main() {
  int64_t n = 0;
  std::cin >> n;
  if (n < 3) {
    std::cout << "NO";
    return 0;
  }
  std::vector<Geometry::Point> poly(n);
  for (int64_t i = 0; i < n; i++) {
    std::cin >> poly[i].x >> poly[i].y;
  }
  int64_t first_product = 0;
  bool sign = false;
  for (int i = 0; i < n; ++i) {
    int64_t prev = (i - 1 + n) % n;
    int64_t curr = i;
    int64_t next = (i + 1) % n;
    first_product =
        Geometry::VectorProduct(Geometry::Vector(poly[prev], poly[curr]), Geometry::Vector(poly[curr], poly[next]));
    if (first_product != 0) {
      sign = (first_product < 0);
      break;
    }
  }
  if (first_product == 0) {
    std::cout << "NO";
    return 0;
  }
  for (int64_t i = 0; i < n; ++i) {
    int64_t prev = (i - 1 + n) % n;
    int64_t curr = i;
    int64_t next = (i + 1) % n;
    int64_t product =
        Geometry::VectorProduct(Geometry::Vector(poly[prev], poly[curr]), Geometry::Vector(poly[curr], poly[next]));
    if (product != 0 && (product < 0) != sign) {
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";
  return 0;
}