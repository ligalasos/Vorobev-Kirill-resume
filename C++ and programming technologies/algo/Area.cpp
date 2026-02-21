#include <iostream>
#include <vector>
#include <iomanip>

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
  };

  static int64_t VectorProduct(const Vector& a, const Vector& b) {
    return a.x * b.y - a.y * b.x;
  }
};

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Geometry::Point> polygon(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> polygon[i].x >> polygon[i].y;
  }

  int64_t area = 0;
  for (int i = 0; i < n; ++i) {
    const auto& p1 = polygon[i];
    const auto& p2 = polygon[(i + 1) % n];
    area += Geometry::VectorProduct({p1.x, p1.y}, {p2.x, p2.y});
  }

  std::cout << std::fixed << std::setprecision(1) << std::abs(static_cast<long double>(area)) / 2.0 << std::endl;
  return 0;
}