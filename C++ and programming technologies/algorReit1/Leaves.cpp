//сдал
#include <iostream>

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

void GoInsert(Node* current, int new_value);

void PostOrder(Node* current);

void DeleteTree(Node* root);

int main() {
  int value = 0;
  std::cin >> value;
  Node* root = new Node{value};
  while (value != 0) {
    int value = 0;
    std::cin >> value;
    if (value == 0) {
      break;
    }
    GoInsert(root, value);
  }
  PostOrder(root);
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

void PostOrder(Node* current) {
  if (current == nullptr) {
    return;
  }
  PostOrder(current->left);
  PostOrder(current->right);
  if (current->left == nullptr and current->right == nullptr) {
    std::cout << current->value << " ";
  }
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}