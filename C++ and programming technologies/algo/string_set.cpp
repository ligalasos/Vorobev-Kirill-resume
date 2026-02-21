#include <iostream>
#include <string>
#include <unordered_set>
#include <cstdint>

#define BIG_CONSTANT(x) (x##LLU)

uint64_t MurmurHash64A(const void* key, int len, uint64_t seed) {
  const uint64_t m = BIG_CONSTANT(0xc6a4a7935bd1e995);
  const int r = 47;

  uint64_t h = seed ^ (len * m);

  const auto* data = static_cast<const uint64_t*>(key);
  const uint64_t* end = data + (len / 8);

  while (data != end) {
    uint64_t k = *data++;

    k *= m;
    k ^= k >> r;
    k *= m;

    h ^= k;
    h *= m;
  }

  const auto* data2 = reinterpret_cast<const unsigned char*>(data);

  switch (len & 7) {
    case 7:
      h ^= static_cast<uint64_t>(data2[6]) << 48;
    case 6:
      h ^= static_cast<uint64_t>(data2[5]) << 40;
    case 5:
      h ^= static_cast<uint64_t>(data2[4]) << 32;
    case 4:
      h ^= static_cast<uint64_t>(data2[3]) << 24;
    case 3:
      h ^= static_cast<uint64_t>(data2[2]) << 16;
    case 2:
      h ^= static_cast<uint64_t>(data2[1]) << 8;
    case 1:
      h ^= static_cast<uint64_t>(data2[0]);
      h *= m;
  }

  h ^= h >> r;
  h *= m;
  h ^= h >> r;

  return h;
}

struct MurmurHash {
  uint64_t seed;

  explicit MurmurHash(uint64_t seed = 0) : seed(seed) {
  }

  size_t operator()(const std::string& key) const {
    return MurmurHash64A(key.data(), static_cast<int>(key.size()), seed);
  }
};

int main() {
  std::unordered_set<std::string, MurmurHash> murmur;
  std::string str;
  std::string op;
  while (std::cin >> op && op != "#") {
    std::cin >> str;
    if (op == "-") {
      murmur.erase(str);
    } else if (op == "+") {
      murmur.insert(str);
    } else if (op == "?") {
      if (murmur.find(str) != murmur.end()) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
  return 0;
}