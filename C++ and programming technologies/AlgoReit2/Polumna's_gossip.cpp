#include <iostream>

size_t Strlen(const char* str) {
  int size = 0;
  while (str[size] != '\0') {
    ++size;
  }
  return size;
}

int main() {
  char input[10001];
  char arr_two[10001];
  std::cin.getline(input, 10001);
  int len = 0;
  while (input[len] != '\0') {
    ++len;
  }
  char arr_one[10001];
  for (int i = 0; i < len; ++i) {
    arr_one[i + 1] = input[i];
  }
  arr_one[len + 1] = '\0';
  for (int i = 1; i <= len; ++i) {
    arr_two[i] = arr_one[len - i + 1];
  }
  arr_two[len + 1] = '\0';
  int** dp = new int*[len + 1];
  for (int i = 0; i < len + 1; ++i) {
    dp[i] = new int[len + 1];
  }
  for (int i = 0; i < len + 1; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i < len + 1; ++i) {
    dp[0][i] = 0;
  }
  for (int i = 1; i < len + 1; ++i) {
    for (int j = 1; j < len + 1; ++j) {
      if (arr_one[i] == arr_two[j]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }
  // std::cout << arr_one + 1 << "\n";
  // std::cout << arr_two + 1 << "\n";
  // for (int i = 0; i < len + 1; ++i) {
  //   for (int j = 0; j < len + 1; ++j) {
  //     std::cout << dp[i][j] << " ";
  //   }
  //   std::cout << "\n";
  // }
  // std::cout << "\n";
  std::cout << len - dp[len][len];
  return 0;
}