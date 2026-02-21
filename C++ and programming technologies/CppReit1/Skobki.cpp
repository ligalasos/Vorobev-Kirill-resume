#include <iostream>

class Stack {
 private:
  struct StackNode {
    int data;
    StackNode* next;
  };

  StackNode* current_node_;

 public:
  Stack() : current_node_(nullptr) {
  }

  ~Stack() {
    while (current_node_ != nullptr) {
      StackNode* temp = current_node_;
      current_node_ = current_node_->next;
      delete temp;
    }
  }

  void Push(int value) {
    auto* new_node = new StackNode{value, current_node_};
    current_node_ = new_node;
  }

  void Pop() {
    if (current_node_ == nullptr) {
      return;
    }
    StackNode* temp = current_node_;
    current_node_ = current_node_->next;
    delete temp;
  }

  int Peek() const {
    if (current_node_ == nullptr) {
      return -1;
    }
    return current_node_->data;
  }

  bool IsFree() const {
    return current_node_ == nullptr;
  }
};

int main() {
  Stack stack;
  char sym = ' ';
  bool psp = true;
  while (std::cin >> sym) {
    if (sym == '(' || sym == '[' || sym == '{') {
      stack.Push(sym);
    } else if (sym == ')') {
      if (stack.Peek() == '(') {
        stack.Pop();
      } else {
        psp = false;
      }
    } else if (sym == ']') {
      if (stack.Peek() == '[') {
        stack.Pop();
      } else {
        psp = false;
      }
    } else if (sym == '}') {
      if (stack.Peek() == '{') {
        stack.Pop();
      } else {
        psp = false;
      }
    }
  }
  if (stack.IsFree() && psp) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }
  return 0;
}
