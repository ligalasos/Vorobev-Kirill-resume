#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct Point {
  int64_t x = 0;
  int64_t y = 0;
};

class PointComparator {
 public:
  explicit PointComparator(const Point& min) : min_point_(min) {
  }

  bool operator()(const Point& a, const Point& b) const {
    const int64_t x1 = a.x - min_point_.x;
    const int64_t y1 = a.y - min_point_.y;
    const int64_t x2 = b.x - min_point_.x;
    const int64_t y2 = b.y - min_point_.y;

    const int64_t cross_product = x1 * y2 - y1 * x2;
    if (cross_product != 0) {
      return cross_product > 0;
    }
    return (x1 * x1 + y1 * y1) >= (x2 * x2 + y2 * y2);
  }

 private:
  Point min_point_;
};

bool IsNonLeftTurn(const Point& a, const Point& b, const Point& c) {
  const int64_t x1 = b.x - a.x;
  const int64_t y1 = b.y - a.y;
  const int64_t x2 = c.x - b.x;
  const int64_t y2 = c.y - b.y;

  const int64_t cross_product = x1 * y2 - y1 * x2;
  return (cross_product <= 0) || (x2 == 0 && y2 == 0);
}

struct Vector {
  int64_t x = 0;
  int64_t y = 0;
};

int64_t CrossProduct(const Vector& a, const Vector& b) {
  return a.x * b.y - a.y * b.x;
}

Point FindMinPoint(const std::vector<Point>& points) {
  Point min_point = points.front();
  for (const auto& point : points) {
    if (point.x < min_point.x || (point.x == min_point.x && point.y < min_point.y)) {
      min_point = point;
    }
  }
  return min_point;
}

std::vector<Point> BuildConvexHull(std::vector<Point> points) {
  if (points.empty()) {
    return {};
  }

  const Point min_point = FindMinPoint(points);

  std::sort(points.begin(), points.end(), PointComparator(min_point));

  std::vector<Point> convex_hull;
  for (const auto& point : points) {
    if (point.x == min_point.x && point.y == min_point.y) {
      continue;
    }

    while (convex_hull.size() >= 2) {
      const Point& a = convex_hull[convex_hull.size() - 2];
      const Point& b = convex_hull.back();
      const Point& c = point;

      if (!IsNonLeftTurn(a, b, c)) {
        break;
      }

      const Vector ab{b.x - a.x, b.y - a.y};
      const Vector bc{c.x - b.x, c.y - b.y};

      const int64_t dot_product = ab.x * bc.x + ab.y * bc.y;
      if (dot_product < 0 && CrossProduct(ab, bc) == 0) {
        break;
      }

      convex_hull.pop_back();
    }
    convex_hull.push_back(point);
  }

  while (convex_hull.size() >= 2) {
    const Point& a = convex_hull[convex_hull.size() - 2];
    const Point& b = convex_hull.back();
    const Point& c = min_point;

    if (!IsNonLeftTurn(a, b, c)) {
      break;
    }

    const Vector ab{b.x - a.x, b.y - a.y};
    const Vector bc{c.x - b.x, c.y - b.y};

    const int64_t dot_product = ab.x * bc.x + ab.y * bc.y;
    if (dot_product < 0 && CrossProduct(ab, bc) == 0) {
      break;
    }

    convex_hull.pop_back();
  }
  convex_hull.push_back(min_point);

  return convex_hull;
}

int64_t CalculatePolygonArea(const std::vector<Point>& polygon) {
  if (polygon.size() < 3) {
    return 0;
  }

  int64_t area = 0;
  const size_t n = polygon.size();
  for (size_t i = 0; i < n; ++i) {
    const Point& current = polygon[i];
    const Point& next = polygon[(i + 1) % n];
    area += (current.x * next.y) - (next.x * current.y);
  }

  return std::abs(area);
}

void PrintResults(const std::vector<Point>& convex_hull, int64_t area) {
  std::cout << convex_hull.size() << '\n';
  for (auto it = convex_hull.rbegin(); it != convex_hull.rend(); ++it) {
    std::cout << it->x << ' ' << it->y << '\n';
  }

  if (area % 2 == 0) {
    std::cout << area / 2 << ".0\n";
  } else {
    std::cout << area / 2 << ".5\n";
  }
}

int main() {
  int n = 0;
  std::cin >> n;

  std::vector<Point> points(n);
  for (auto& point : points) {
    std::cin >> point.x >> point.y;
  }

  const std::vector<Point> convex_hull = BuildConvexHull(points);
  const int64_t area = CalculatePolygonArea(convex_hull);

  PrintResults(convex_hull, area);

  return 0;
}