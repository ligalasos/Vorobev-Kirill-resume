#include <iostream>

class Deque {
 private:
  struct Node {
    int value = 0;
    Node* next = nullptr;
    Node* pred = nullptr;
  };
  int size_ = 0;
  Node* last_ = nullptr;
  Node* first_ = nullptr;

 public:
  void Pushfront(int new_value) {
    if (size_ == 0) {
      auto next = new Node{new_value};
      last_ = next;
      first_ = next;
    } else {
      auto new_elem = new Node{new_value};
      first_->pred = new_elem;
      new_elem->next = first_;
      first_ = new_elem;
    }
    size_ += 1;
  }

  void Pushback(int new_value) {
    if (size_ == 0) {
      auto new_elem = new Node{new_value};
      last_ = new_elem;
      first_ = new_elem;
    } else {
      auto new_elem = new Node{new_value};
      last_->next = new_elem;
      new_elem->pred = last_;
      last_ = new_elem;
    }
    ++size_;
  }

  void Popback() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_ == 1) {
      delete last_;
      last_ = nullptr;
      first_ = nullptr;
      --size_;
    } else {
      auto pop_elem = last_;
      last_->pred->next = nullptr;
      last_ = last_->pred;
      delete pop_elem;
      --size_;
    }
  }

  void Popfront() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_ == 0) {
      delete first_;
      last_ = nullptr;
      first_ = nullptr;
      --size_;
    } else {
      auto pop_elem = first_;
      first_->next->pred = nullptr;
      first_ = first_->next;
      delete pop_elem;
      --size_;
    }
  }

  int64_t Front() {
    return first_->value;
  }

  int64_t Back() {
    return last_->value;
  }

  int64_t Size() {
    return size_;
  }

  void Clear() {
    while (size_ > 0) {
      Popback();
    }
  }
};

bool Vvod(const char* str1, const char* str2) {
  size_t i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) {
      return false;
    }
    ++i;
  }
  return str1[i] == '\0' && str2[i] == '\0';
}

int main() {
  Deque deque;
  int n = 0;
  int x = 0;
  char command[11] = "";
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (Vvod(command, "push_back")) {
      std::cin >> x;
      deque.Pushback(x);
      std::cout << "ok\n";
    } else if (Vvod(command, "push_front")) {
      std::cin >> x;
      deque.Pushfront(x);
      std::cout << "ok\n";
    } else if (Vvod(command, "pop_back")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Back() << '\n';
        deque.Popback();
      }
    } else if (Vvod(command, "pop_front")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Front() << '\n';
        deque.Popfront();
      }
    } else if (Vvod(command, "size")) {
      std::cout << deque.Size() << '\n';
    } else if (Vvod(command, "clear")) {
      deque.Clear();
      std::cout << "ok\n";
    } else if (Vvod(command, "back")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Back() << '\n';
      }
    } else if (Vvod(command, "front")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Front() << '\n';
      }
    } else {
      std::cout << "bye\n";
      break;
    }
  }
  deque.Clear();
  return 0;
}
