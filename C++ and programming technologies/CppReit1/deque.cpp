
#include <iostream>
#include <cassert>

class DequeLong {
  struct Node {
    int64_t data;
    Node* next = nullptr;
    Node* prev = nullptr;

    explicit Node(int64_t data, Node* next = nullptr, Node* prev = nullptr) : data(data), next(next), prev(prev) {
    }
  };

  size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;

 public:
  void PushBack(int64_t data) {
    Node* tmp = new Node(data, nullptr, last_);

    if (last_) {
      last_->next = tmp;
    } else {
      first_ = tmp;
    }

    last_ = tmp;
    ++size_;
  }

  void PushFront(int64_t data) {
    Node* tmp = new Node(data, first_, nullptr);

    if (first_) {
      first_->prev = tmp;
    } else {
      last_ = tmp;
    }

    first_ = tmp;
    ++size_;
  }

  void PopBack() {
    last_ = last_->prev;
    if (!last_) {
      delete first_;
      first_ = nullptr;
    } else {
      delete last_->next;
      last_->next = nullptr;
    }
    --size_;
  }

  void PopFront() {
    first_ = first_->next;
    if (!first_) {
      delete last_;
      last_ = nullptr;
    } else {
      delete first_->prev;
      first_->prev = nullptr;
    }
    --size_;
  }

  int64_t Front() {
    return first_->data;
  }

  int64_t Back() {
    return last_->data;
  }

  size_t Size() {
    return size_;
  }

  void Clear() {
    Node* curr = first_;
    while (curr) {
      Node* tmp = curr;
      curr = curr->next;
      delete tmp;
    }

    size_ = 0;
    first_ = nullptr;
    last_ = nullptr;
  }

  void Print() {
    Node* curr = first_;
    while (curr) {
      std::cout << curr->data << ' ';
      assert((curr == first_) || (curr->prev->next == curr));
      curr = curr->next;
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
  DequeLong deque;
  char command[11] = "";
  int64_t x = 0;
  size_t commands_count = 0;
  std::cin >> commands_count;
  size_t i = 0;
  while (i < commands_count) {
    std::cin >> command;
    if (Vvod(command, "push_back")) {
      std::cin >> x;
      deque.PushBack(x);
      std::cout << "ok\n";
    } else if (Vvod(command, "push_front")) {
      std::cin >> x;
      deque.PushFront(x);
      std::cout << "ok\n";
    } else if (Vvod(command, "pop_back")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Back() << '\n';
        deque.PopBack();
      }
    } else if (Vvod(command, "pop_front")) {
      if (deque.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << deque.Front() << '\n';
        deque.PopFront();
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
    std::cout << "DEBUG: deque size - " << deque.Size() << '\n';
    std::cout << "DEBUG: deque - "; deque.Print(); std::cout << '\n';
    ++i;
  }
  deque.Clear();
}
