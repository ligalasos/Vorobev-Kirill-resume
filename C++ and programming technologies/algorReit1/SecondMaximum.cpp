//сдал
#include <iostream>

struct Node {
  int value = 0;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

void GoInsert(Node* current, int new_value);

int GetMax(Node* current);

void DeleteTree(Node* root);

int main() {
  int n = 0;
  std::cin >> n;
  Node* root = new Node{n};
  root->parent = nullptr;
  GoInsert(root, n);
  while (n != 0) {
    std::cin >> n;
    if (n == 0) {
      break;
    }
    GoInsert(root, n);
  }
  std::cout << GetMax(root);
  DeleteTree(root);
  return 0;
}

void GoInsert(Node* current, int new_value) {
  if (new_value == current->value) {
    return;
  }
  if (new_value > current->value) {
    if (current->right == nullptr) {
      current->right = new Node{};
      current->right->value = new_value;
      current->right->parent = current;
      return;
    }
    GoInsert(current->right, new_value);
  } else {
    if (current->left == nullptr) {
      current->left = new Node{};
      current->left->value = new_value;
      current->left->parent = current;
      return;
    }
    GoInsert(current->left, new_value);
  }
}

int GetMax(Node* current) {
  if (current == nullptr) {
    return 0;
  }
  while (current->right != nullptr) {
    current = current->right;
  }
  if (current->left != nullptr) {
    current = current->left;
    while (current->right != nullptr) {
      current = current->right;
    }
    return current->value;
  }
  return current->parent->value;
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}