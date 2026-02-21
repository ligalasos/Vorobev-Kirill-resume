#include <iostream>
#include <deque>

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n;
  std::deque<int64_t> one(n + 1);
  for (int i = 1; i <= n; ++i) {
    std::cin >> one[i];
  }
  std::cin >> m;
  std::deque<int64_t> two(m + 1);
  for (int i = 1; i <= m; ++i) {
    std::cin >> two[i];
  }
  std::deque<std::deque<int>> dp(n + 1, std::deque<int>(m + 1, 0));
  std::deque<std::deque<int>> arr_one(n + 1, std::deque<int>(m + 1));
  std::deque<std::deque<int>> arr_two(n + 1, std::deque<int>(m + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (one[i] == two[j]) {
        dp[i][j] = 1;
        for (int k = 1; k < i; ++k) {
          if (one[k] < one[i] and dp[i][j] < dp[k][j] + 1) {
            dp[i][j] = dp[k][j] + 1;
            arr_one[i][j] = k;
            arr_two[i][j] = j;
          }
        }
      } else {
        dp[i][j] = dp[i][j - 1];
        arr_one[i][j] = arr_one[i][j - 1];
        arr_two[i][j] = arr_one[i][j - 1];
      }
    }
  }
  int max = 0;
  int x = 0;
  int y = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (dp[i][j] > max) {
        max = dp[i][j];
        x = i;
        y = j;
      }
    }
  }
  std::cout << max << "\n";
  std::deque<int64_t> a;
  while (x != 0) {
    a.push_front(one[x]);
    int x0 = x;
    x = arr_one[x][y];
    y = arr_two[x0][y];
  }
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << " ";
  }
  return 0;
}


// #include <iostream>
// #include <vector>
// #include <algorithm>

// int main() {
//   int n = 0;
//   int m = 0;
//   std::cin >> n;
//   auto one = new int64_t[n + 1];
//   for (int i = 1; i <= n; ++i) {
//     std::cin >> one[i];
//   }
//   std::cin >> m;
//   auto two = new int64_t[m + 1];
//   for (int i = 1; i <= m; ++i) {
//     std::cin >> two[i];
//   }

//   int** dp = new int*[n + 1];
//   int** arr_one = new int*[n + 1];
//   int** arr_two = new int*[n + 1];
//   for (int i = 0; i <= n; ++i) {
//     dp[i] = new int[m + 1]();
//     arr_one[i] = new int[m + 1]();
//     arr_two[i] = new int[m + 1]();
//   }

//   for (int i = 1; i <= n; ++i) {
//     for (int j = 1; j <= m; ++j) {
//       if (one[i] == two[j]) {
//         dp[i][j] = 1;
//         for (int k = 1; k < i; ++k) {
//           // for (int r = 1; r < j; ++r) {
//           //   if (dp[i][j] < dp[k][r] + 1 && one[k] < one[i] && one[k] == two[r]) {
//           //     dp[i][j] = dp[k][r] + 1;
//           //     arr_one[i][j] = k;
//           //     arr_two[i][j] = r;
//           //   }
//           // }
//           if (one[k] < one[i] and dp[i][j] < dp[k][j] + 1) {
//             dp[i][j] = dp[k][j] + 1;
//             arr_one[i][j] = k;
//             arr_two[i][j] = j;
//           }
//         }
//       } else {
//         dp[i][j] = dp[i][j - 1];
//         arr_one[i][j] = i;
//         arr_two[i][j] = j - 1;
//       }
//     }
//   }

//   int max = 0;
//   int x = 0;
//   int y = 0;
//   for (int i = 1; i <= n; ++i) {
//     for (int j = 1; j <= m; ++j) {
//       if (dp[i][j] > max) {
//         max = dp[i][j];
//         x = i;
//         y = j;
//       }
//     }
//   }

//   std::cout << max << "\n";
//   std::vector<int64_t> a;
//   while (x != 0) {
//     a.push_back(one[x]);
//     int x0 = x;
//     x = arr_one[x][y];
//     y = arr_two[x0][y];
//   }
//   std::reverse(a.begin(), a.end());
//   for (size_t i = 0; i < a.size(); ++i) {
//     std::cout << a[i] << " ";
//   }
//   std::cout << "\n";

//   delete[] one;
//   delete[] two;
//   for (int i = 0; i <= n; ++i) {
//     delete[] dp[i];
//     delete[] arr_one[i];
//     delete[] arr_two[i];
//   }
//   delete[] dp;
//   delete[] arr_one;
//   delete[] arr_two;

//   return 0;
// }
