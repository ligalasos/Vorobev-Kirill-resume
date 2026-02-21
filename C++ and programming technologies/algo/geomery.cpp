#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
namespace Geometry {

struct Vector {
  double x = 0;
  double y = 0;

  Vector(double x, double y) : x(x), y(y) {
  }

  Vector(Point x, Point y) {
    x = y.x - x.x;
    y = y.y - x.y;
  }

  Vector operator+(const Vector& b) {
    return {x + b.x, y + b.y};
  }

  Vector operator-(const Vector& b) {
    return {x - b.x, y - b.y};
  }

  Vector operator-() {
    return {-x, -y};
  }

  Vector operator*(double k) {
    return {k * x, k * y};
  }

  Vector operator/(double k) {
    return {x / k, y / k};
  }

  Vector& operator=(const Vector& b) {
    if (this != &b) {
      this->x = b.x;
      this->y = b.y;
    }
    return *this;
  }

  bool operator==(const Vector& b) const {
    return (x == b.x and y == b.y);
  }

  static Vector VectorSum(Vector a, Vector b) {
    return {Vector(a.x + b.x, a.y + b.y)};
  }

  static double DotProduct(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
  }

  static double VectorProduct(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
  }
};

class IShape {
 public:
  virtual ~IShape() = default;
  virtual IShape& Move(const Vector& vector) = 0;
  virtual bool ContainsPoint(const Point& point) const = 0;
  virtual bool CrossesSegment(const Segment& segment) const = 0;
  virtual std::unique_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;
};


  class Point : public IShape {
  public:
    double x = 0;
    double y = 0;

    Point (double x, double y) : x(x), y(y) {}
    
    IShape& Move (const Vector& point) override {
      this->x = x + point.x;
      this->y = y + point.y;
      return *this;
    }

    bool Point::ContainsPoint(const Point& point) const {
      return x == point.x && y == point.y;
    }

    bool CrossesSegment(const Segment& segment) const {

    }
  };



  struct Line : public IShape {
    double a = 0;
    double b = 0;
    double c = 0;
  };

  struct Ray : public IShape {
    Point p;
    Vector v;
  };

  struct Segment : public IShape {
    Point a;
    Point b;
  };

  struct Polygon : public IShape {
    std::vector<Point> v;
  };

  struct Circle : public IShape {
    Point o;
    double r;
  };




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


}

