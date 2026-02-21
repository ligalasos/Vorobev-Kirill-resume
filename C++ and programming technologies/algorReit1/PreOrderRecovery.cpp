#include <climits>
#include <iostream>

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
};

Node* BuildTree(int*& arr, int& lol, int minimum, int maximum, int n);

void PostOrder(Node* root);

void DeleteTree(Node* root);

int main() {
  int n = 0;
  std::cin >> n;
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  int lol = 0;
  Node* root = BuildTree(arr, lol, INT_MIN, INT_MAX, n);
  PostOrder(root);
  DeleteTree(root);
  delete[] arr;
  return 0;
}

Node* BuildTree(int*& arr, int& lol, int minimum, int maximum, int n) {
  if (lol >= n or arr[lol] < minimum or arr[lol] > maximum) {
    return nullptr;
  }
  Node* root = new Node{arr[lol++]};
  root->left = BuildTree(arr, lol, minimum, root->value, n);
  root->right = BuildTree(arr, lol, root->value, maximum, n);
  return root;
}

void PostOrder(Node* root) {
  if (root == nullptr) {
    return;
  }
  PostOrder(root->left);
  PostOrder(root->right);
  std::cout << root->value << " ";
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}