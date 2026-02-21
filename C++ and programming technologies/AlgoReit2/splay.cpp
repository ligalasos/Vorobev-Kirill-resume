#include <algorithm>
#include <cmath>
#include <iostream>

struct Node {
  int64_t value{0};
  Node* parent{nullptr};
  Node* left{nullptr};
  Node* right{nullptr};
};

void SetParent(Node* child, Node* parent) {
  if (child != nullptr) {
    child->parent = parent;
  }
}
void KeepParent(Node* root) {
  if (root != nullptr) {
    SetParent(root->left, root);
    SetParent(root->right, root);
  }
}

void Rotate(Node* parent, Node* child) {
  if (parent == nullptr) {
    return;
  }
  Node* grandparent = parent->parent;
  if (grandparent != nullptr) {
    if (grandparent->left == parent) {
      grandparent->left = child;
    } else {
      grandparent->right = child;
    }
  }
  if (parent->left == child) {
    parent->left = child->right;
    child->right = parent;
  } else {
    parent->right = child->left;
    child->left = parent;
  }
  KeepParent(child);
  KeepParent(parent);
  child->parent = grandparent;
}

Node* Splay(Node* cur) {
  if (cur == nullptr) {
    return nullptr;
  }
  Node* parent = cur->parent;
  if (parent == nullptr) {
    return cur;
  }
  Node* grandparent = parent->parent;

  if (grandparent == nullptr) {
    Rotate(parent, cur);
    return cur;
  }

  const bool is_zig_zig = (grandparent->left == parent) == (parent->left == cur);

  if (is_zig_zig) {
    Rotate(grandparent, parent);
    Rotate(parent, cur);
  } else {
    Rotate(parent, cur);
    Rotate(grandparent, cur);
  }
  return Splay(cur);
}

Node* Find(Node* cur, const int64_t val) {
  if (cur == nullptr) {
    return nullptr;
  }
  if (cur->value == val) {
    return Splay(cur);
  }

  if (val < cur->value && cur->left != nullptr) {
    return Find(cur->left, val);
  }
  if (val > cur->value && cur->right != nullptr) {
    return Find(cur->right, val);
  }
  return Splay(cur);
}

std::pair<Node*, Node*> Split(Node* cur, const int64_t val) {
  if (cur == nullptr) {
    return {nullptr, nullptr};
  }
  cur = Find(cur, val);
  if (cur->value < val) {
    Node* right = cur->right;
    cur->right = nullptr;
    return {cur, right};
  }
  Node* left = cur->left;
  cur->left = nullptr;
  return {left, cur};
}

Node* Merge(Node* left, Node* right) {
  if (left == nullptr) {
    return right;
  }
  if (right == nullptr) {
    return left;
  }
  right = Find(right, left->value);
  right->left = left;
  left->parent = right;
  return right;
}

Node* Insert(Node* root, int64_t key) {
  auto result = Split(root, key);
  Node* left = result.first;
  Node* right = result.second;
  root = new Node;
  root->value = key;
  root->left = left;
  root->right = right;
  KeepParent(root);
  return root;
}

Node* Remove(Node* root, const int64_t value) {
  root = Find(root, value);
  if (root == nullptr || root->value != value) {
    return nullptr;
  }
  SetParent(root->left, nullptr);
  SetParent(root->right, nullptr);
  return Merge(root->left, root->right);
}

void PreOrder(Node* root) {
  if (root == nullptr) {
    return;
  }
  std::cout << root->value << " ";
  PreOrder(root->left);
  PreOrder(root->right);
}

Node* Next(Node* node, int64_t val, int64_t& res) {
  Node* result_node = nullptr;

  while (node != nullptr) {
    if (node->value >= val) {
      res = node->value;
      result_node = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }

  if (result_node != nullptr) {
    return Splay(result_node);
  }
  return Splay(node);
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}

int main() {
  int64_t res = -228;
  const int d = 1000000000;
  Node* root = nullptr;
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int64_t x = 0;
    char command = 0;
    std::cin >> command;
    std::cin >> x;
    if (command == '?') {
      res = -1;
      root = Next(root, x, res);
      std::cout << res << '\n';
    } else {
      int64_t key = 0;
      if (res != -228) {
        key = (x + res) % d;
      } else {
        key = x;
      }
      root = Insert(root, key);
      res = -228;
    }
  }
  DeleteTree(root);
  return 0;
}
