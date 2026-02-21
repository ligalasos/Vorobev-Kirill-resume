#include <iostream>

struct Node {
  int64_t value = 0;
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
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

Node* Splay(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node* parent = node->parent;
  if (parent == nullptr) {
    return node;
  }
  Node* grandparent = parent->parent;
  if (grandparent == nullptr) {
    Rotate(parent, node);
    return node;
  }
  const bool is_zig_zig = (grandparent->left == parent) == (parent->left == node);
  if (is_zig_zig) {
    Rotate(grandparent, parent);
    Rotate(parent, node);
  } else {
    Rotate(parent, node);
    Rotate(grandparent, node);
  }
  return Splay(node);
}

Node* Find(Node* cur, int64_t val) {
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

Node* Next(Node* node, int64_t val, int64_t& res) {
  while (node != nullptr) {
    if (node->value >= val) {
      res = node->value;
      if (node->left != nullptr) {
        node = node->left;
        continue;
      }
      break;
    }
    if (node->value < val && node->right != nullptr) {
      node = node->right;
      continue;
    }
    break;
  }
  return Splay(node);
}

std::pair<Node*, Node*> Split(Node* node, int64_t val) {
  if (node == nullptr) {
    return {nullptr, nullptr};
  }
  node = Find(node, val);
  if (node->value < val) {
    Node* right = node->right;
    node->right = nullptr;
    return {node, right};
  }
  Node* left = node->left;
  node->left = nullptr;
  return {left, node};
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

Node* Insert(Node* root, int64_t val) {
  auto p = Split(root, val);
  root = new Node;
  root->value = val;
  root->left = p.first;
  root->right = p.second;
  SetParent(p.first, root);
  SetParent(p.second, root);
  return root;
}

void DeleteTree(Node* root) {
  if (root != nullptr) {
    DeleteTree(root->left);
    DeleteTree(root->right);
    delete root;
  }
}

const int64_t kD = 1000000000;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  Node* root = nullptr;
  int n = 0;
  std::cin >> n;
  char com = 0;
  int64_t z = 0;
  int64_t result = -2;
  for (int i = 0; i < n; ++i) {
    std::cin >> com;
    std::cin >> z;
    if (com == '?') {
      result = -1;
      root = Next(root, z, result);
      std::cout << result << '\n';
    } else {
      if (result != -2) {
        root = Insert(root, (z + result) % kD);
        result = -2;
      } else {
        root = Insert(root, z);
      }
    }
  }
  DeleteTree(root);
}