#include <iostream>

class Deque {
 private:
  struct Node {
    int64_t value = 0;
    Node* next = nullptr;
    Node* pred = nullptr;
  };
  int64_t size_ = 0;
  Node* last_ = nullptr;
  Node* first_ = nullptr;

 public:
  void Pushfront(int64_t new_value) {
    auto new_elem = new Node{new_value};
    if (size_ == 0) {
      last_ = new_elem;
      first_ = new_elem;
    } else {
      first_->pred = new_elem;
      new_elem->next = first_;
      first_ = new_elem;
    }
    size_ += 1;
  }

  void Pushback(int64_t new_value) {
    auto new_elem = new Node{new_value};
    if (size_ == 0) {
      last_ = new_elem;
      first_ = new_elem;
    } else {
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
      first_ = last_ = nullptr;
    } else {
      auto pop_elem = last_;
      last_ = last_->pred;
      last_->next = nullptr;
      delete pop_elem;
    }
    --size_;
  }

  void Popfront() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    if (size_ == 1) {
      delete first_;
      first_ = last_ = nullptr;
    } else {
      auto pop_elem = first_;
      first_ = first_->next;
      first_->pred = nullptr;
      delete pop_elem;
    }
    --size_;
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

class MinQueue {
 private:
  Deque queue_;
  Deque queue_of_min_;

 public:
  void Enqueue(int64_t value) {
    if (SizeQueue() == 0) {
      queue_.Pushback(value);
      queue_of_min_.Pushback(value);
      return;
    }
    queue_.Pushback(value);
    while (queue_of_min_.Size() and queue_of_min_.Back() > value) {
      queue_of_min_.Popback();
    }
    queue_of_min_.Pushback(value);
  }

  void Dequeue() {
    int64_t value = queue_.Front();
    queue_.Popfront();
    if (value == queue_of_min_.Front()) {
      queue_of_min_.Popfront();
    }
  }

  int64_t Front() {
    return queue_.Front();
  }

  int64_t Back() {
    return queue_.Back();
  }

  int64_t Minimum() {
    return queue_of_min_.Front();
  }

  int64_t SizeQueue() {
    return queue_.Size();
  }

  void Clear() {
    queue_.Clear();
    queue_of_min_.Clear();
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
  MinQueue queue;
  int n = 0;
  int x = 0;
  char command[11] = "";
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> command;
    if (Vvod(command, "enqueue")) {
      std::cin >> x;
      queue.Enqueue(x);
      std::cout << "ok\n";
    } else if (Vvod(command, "dequeue")) {
      if (queue.SizeQueue() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Front() << "\n";
        queue.Dequeue();
      }
    } else if (Vvod(command, "front")) {
      if (queue.SizeQueue() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Front() << '\n';
      }
    } else if (Vvod(command, "size")) {
      std::cout << queue.SizeQueue() << '\n';
    } else if (Vvod(command, "clear")) {
      if (queue.SizeQueue() == 0) {
        std::cout << "ok\n";
      } else {
        queue.Clear();
        std::cout << "ok\n";
      }
    } else if (Vvod(command, "min")) {
      if (queue.SizeQueue() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Minimum() << '\n';
      }
    }
  }
  queue.Clear();
  return 0;
}

// Ввод	Вывод
// 9
// enqueue 2
// front
// dequeue
// size
// dequeue
// enqueue 1
// enqueue 2
// size
// min

// ok
// 2
// 2
// 0
// error
// ok
// ok
// 2
// 1