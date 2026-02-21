#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

class Geometry {
 public:
  struct Point {
    double x = 0;
    double y = 0;
  };

  struct Vector {
    double x = 0;
    double y = 0;

    Vector(double x, double y) : x(x), y(y) {
    }
  };

  struct Line {
    double a = 0;
    double b = 0;
    double c = 0;
  };

  struct Ray {
    Point p;
    Vector v;
  };

  struct Segment {
    Point a;
    Point b;
  };

  struct Polygon {
    std::vector<Point> v;
  };

  static Vector VectorSum(Vector a, Vector b) {
    return {Vector(a.x + b.x, a.y + b.y)};
  }

  static double DotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
  }

  static double VectorProduct(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
  }

  // Line LineSegment(Segment n) {
  //   Line line;
  //   line.a = n.b.y - n.a.y;
  //   line.b = n.a.x - n.b.x;
  //   line.c = -n.a.x * (n.b.y - n.a.y) + n.a.y * (-n.a.x + n.b.x);
  // }

  //  bool SegmentsIntersection(Segment one, Segment two) {
  //   Line lone = LineSegment(one);
  //   Line ltwo = LineSegment(two);
  //   if ((lone.a * one.a.x + lone.b * one.a.y + lone.c) * (lone.a * one.a.x + lone.b * one.a.y + lone.c) > 0
  //   and (lone.a * two.a.x + lone.b * two.a.y + lone.c) * (lone.a * two.a.x + lone.b * two.a.y + lone.c) > 0
  //   and (ltwo.a * one.a.x + ltwo.b * one.a.y + ltwo.c) * (ltwo.a * one.a.x + ltwo.b * one.a.y + ltwo.c) > 0
  //   and (ltwo.a * two.a.x + ltwo.b * two.a.y + ltwo.c) * (ltwo.a * two.a.x + ltwo.b * two.a.y + ltwo.c) > 0) {
  //     return true;
  //   }
  //   return false;
  //  }

  // int LinePointDist(Point point, Line line) {
  //   Point pivot;
  //   pivot.x = 0;
  // }
};

using Point = Geometry::Point;
using Vector = Geometry::Vector;
using Segment = Geometry::Segment;

int main() {
  int n = 0;
  int 
  return 0;
}