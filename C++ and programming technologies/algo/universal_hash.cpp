#include <iostream>
#include <unordered_set>
#include <random>
#include <string>

const int64_t kP = 1'000'000'007;
int64_t a = 0;
int64_t b = 0;

struct Hash {
  size_t operator()(int x) const {
    return ((a * x + b) % kP);
  }
};

void RandomP();

int main() {
  RandomP();
  std::unordered_set<int, Hash> uset;
  int n = 0;
  std::cin >> n;

  for (int i = 0; i < n; ++i) {
    int num = 0;
    std::string op;
    std::cin >> op >> num;

    if (op == "+") {
      uset.insert(num);
    } else if (op == "?") {
      if (uset.find(num) != uset.end()) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    } else if (op == "-") {
      uset.erase(num);
    }
  }

  return 0;
}

void RandomP() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int64_t> dist_a(1, kP - 1);
  std::uniform_int_distribution<int64_t> dist_b(0, kP - 1);

  a = dist_a(gen);
  b = dist_b(gen);
}