#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

class Side {
 public:
  int64_t x = 0;
  bool left_side = true;
  int64_t y1 = 0;
  int64_t y2 = 0;

  Side(int64_t x, bool begin, int64_t y1, int64_t y2) : x(x), left_side(begin), y1(y1), y2(y2) {
  }
};

class Interval {
 public:
  int64_t begin = 0;
  int64_t end = 0;

  Interval(int64_t begin, int64_t end) : begin(begin), end(end) {
  }

  bool operator<(const Interval& other) const {
    if (begin != other.begin) {
      return begin < other.begin;
    }
    return end < other.end;
  }
};

bool Compare(const Side& a, const Side& b) {
  if (a.x == b.x) {
    return a.left_side > b.left_side;
  }
  return a.x < b.x;
}

int64_t MergeRec(std::vector<Side> events) {

  std::sort(events.begin(), events.end(), Compare);

  int64_t square = 0;
  int64_t prev = events[0].x;
  std::map<Interval, int> open_int;

  for (auto& event : events) {
    if (!open_int.empty()) {
      int64_t length = 0;
      int64_t last_y = -1;

      for (const auto& interval : open_int) {
        int64_t start_y = interval.first.begin;
        int64_t end_y = interval.first.end;

        if (start_y > last_y) {
          length += end_y - start_y;
          last_y = end_y;
        } else if (end_y > last_y) {
          length += end_y - last_y;
          last_y = end_y;
        }
      }

      square += length * (event.x - prev);
    }

    Interval current{event.y1, event.y2};

    if (event.left_side) {
      open_int[current]++;
    } else {
      open_int[current]--;
      if (open_int[current] == 0) {
        open_int.erase(current);
      }
    }

    prev = event.x;
  }
  return square;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Side> events;

  for (int i = 0; i < n; ++i) {
    int64_t one_x = 0;
    int64_t one_y = 0;
    int64_t two_x = 0;
    int64_t two_y = 0;
    std::cin >> one_x >> one_y >> two_x >> two_y;
    Side one{one_x, true, one_y, two_y};
    Side two{two_x, false, one_y, two_y};
    events.push_back(one);
    events.push_back(two);
  }

  std::cout << MergeRec(events) << "\n";
  return 0;
}