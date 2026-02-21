#include <iostream>
#include <deque>
#include <algorithm>

class Team {
 public:
  int points_;
  int penalty_;
  int number_;
  Team(int points, int pe, int n) : points_(points), penalty_(pe), number_(n) {
  }
};

bool Comparator(const Team& a, const Team& b) {
  if (a.points_ > b.points_) {
    return true;
  }
  if (a.points_ < b.points_) {
    return false;
  }
  if (a.penalty_ < b.penalty_) {
    return true;
  }
  if (a.penalty_ > b.penalty_) {
    return false;
  }
  if (a.number_ > b.number_) {
    return true;
  }
  return false;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::deque<Team> arr;
  for (int i = 0; i < n; ++i) {
    int points = 0;
    int penalty = 0;
    std::cin >> points >> penalty;
    Team a = Team(points, penalty, i);
    arr.push_back(a);
  }
  std::sort(arr.begin(), arr.end(), Comparator);
  for (int i = 0; i < n; ++i) {
    std::cout << arr[i].number_ + 1 << "\n";
  }
  return 0;
}