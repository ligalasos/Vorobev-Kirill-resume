#include <cmath>
#include <iostream>
#include <climits>

struct Node {
  int value = 0;
  int height = 1;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

int GetHeight(const Node* current_node) {
  if (current_node == nullptr) {
    return 0;
  }
  return current_node->height;
}

int GetBalance(const Node* current_node) {
  if (current_node == nullptr) {
    return 0;
  }
  return GetHeight(current_node->right) - GetHeight(current_node->left);
}

void FixHeight(Node* current_node) {
  if (current_node == nullptr) {
    return;
  }
  current_node->height = std::max(GetHeight(current_node->left), GetHeight(current_node->right)) + 1;
}

Node* SmallLeft(Node* current_node) {
  Node* right_child = current_node->right;
  if (right_child == nullptr) {
    return current_node;
  }
  if (right_child->left != nullptr) {
    right_child->left->parent = current_node;
  }
  current_node->right = right_child->left;

  right_child->parent = current_node->parent;
  if (current_node->parent != nullptr) {
    if (current_node->parent->left == current_node) {
      right_child->parent->left = right_child;
    } else {
      right_child->parent->right = right_child;
    }
  }
  current_node->parent = right_child;
  right_child->left = current_node;
  FixHeight(current_node);
  FixHeight(right_child);
  return right_child;
}

Node* SmallRight(Node* current_node) {
  Node* left_child = current_node->left;
  if (left_child == nullptr) {
    return current_node;
  }
  if (left_child->right != nullptr) {
    left_child->right->parent = current_node;
  }
  current_node->left = left_child->right;

  left_child->parent = current_node->parent;
  if (current_node->parent != nullptr) {
    if (current_node->parent->left == current_node) {
      left_child->parent->left = left_child;
    } else {
      left_child->parent->right = left_child;
    }
  }

  current_node->parent = left_child;
  left_child->right = current_node;

  FixHeight(current_node);
  FixHeight(left_child);
  return left_child;
}

Node* BigRight(Node* current_node) {
  SmallLeft(current_node->left);
  return SmallRight(current_node);
}

Node* BigLeft(Node* current_node) {
  SmallRight(current_node->right);
  return SmallLeft(current_node);
}

void Normalize(Node*& current_node) {
  FixHeight(current_node);
  if (current_node == nullptr || abs(GetBalance(current_node)) <= 1) {
    return;
  }
  if (GetBalance(current_node) == -2) {
    // Дисбаланс в левом поддереве
    if (GetBalance(current_node->left) > 0) {
      // У левого сына, правое поддерево глубже
      current_node = BigRight(current_node);
    } else {
      current_node = SmallRight(current_node);
    }
  } else {
    // Дисбаланс в другую сторону
    if (GetBalance(current_node->right) < 0) {
      current_node = BigLeft(current_node);
    } else {
      current_node = SmallLeft(current_node);
    }
  }
}

void GoInsert(Node*& current_node, int new_value) {
  if (new_value == current_node->value) {
    return;
  }
  if (new_value > current_node->value) {
    if (current_node->right == nullptr) {
      current_node->right = new Node();
      current_node->right->value = new_value;
      current_node->right->parent = current_node;
      Normalize(current_node);
      return;
    }
    GoInsert(current_node->right, new_value);
  } else {
    if (current_node->left == nullptr) {
      current_node->left = new Node();
      current_node->left->value = new_value;
      current_node->left->parent = current_node;
      Normalize(current_node);
      return;
    }
    GoInsert(current_node->left, new_value);
  }
  Normalize(current_node);
}

Node* GetMax(Node* current_node) {
  if (current_node == nullptr) {
    return nullptr;
  }
  while (current_node->right != nullptr) {
    current_node = current_node->right;
  }
  return current_node;
}

Node* GetMin(Node* current_node) {
  if (current_node == nullptr) {
    return nullptr;
  }
  while (current_node->left != nullptr) {
    current_node = current_node->left;
  }
  return current_node;
}

Node* GetPred(Node* current_node) {
  if (current_node == nullptr) {
    return nullptr;
  }
  if (current_node->left != nullptr) {
    return GetMax(current_node->left);
  }
  while (current_node->parent != nullptr) {
    if (current_node->parent->right == current_node) {
      return current_node->parent;
    }
    current_node = current_node->parent;
  }
  return nullptr;
}

void PrintInOrder(const Node* current_node) {
  if (current_node == nullptr) {
    return;
  }
  PrintInOrder(current_node->left);
  std::cout << current_node->value << " ";
  PrintInOrder(current_node->right);
}

void PrintPreOrder(const Node* current_node) {
  if (current_node == nullptr) {
    return;
  }
  std::cout << current_node->value << " ";
  PrintPreOrder(current_node->left);
  PrintPreOrder(current_node->right);
}

void PrintPostOrder(const Node* current_node) {
  if (current_node == nullptr) {
    return;
  }
  PrintPostOrder(current_node->left);
  PrintPostOrder(current_node->right);
  std::cout << current_node->value << " ";
}

int Next(Node* current, int key) {
  int result = -1;
  while (current) {
    if (current->value >= key) {
      result = current->value;
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return result;
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
  int n = 0;
  std::cin >> n;
  Node* root = new Node;
  const int m = 1e9;
  int last = 0;
  for (int i = 0; i < n; ++i) {
    char command = 0;
    std::cin >> command;
    if (command == '+') {
      int value = 0;
      std::cin >> value;
      if (i == 0) {
        root->value = value;
      }
      if (last) {
        value = (value + last) % m;
      }
      GoInsert(root, value);
      last = 0;
    }
    if (command == '?') {
      int value = 0;
      std::cin >> value;
      std::cout << Next(root, value) << "\n";
      last = Next(root, value);
    }
  }
  DeleteTree(root);
  return 0;
}
