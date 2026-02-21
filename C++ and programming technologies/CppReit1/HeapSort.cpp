#ifndef lalka
#define lalka

template <typename T>
void SiftDown(const T begin, const T end, int root, int size) {
  int biggest = root;
  int left_child = 2 * root + 1;
  int right_child = 2 * root + 2;
  if (left_child < size && *(begin + biggest) < *(begin + left_child)) {
    biggest = left_child;
  }
  if (right_child < size && *(begin + biggest) < *(begin + right_child)) {
    biggest = right_child;
  }
  if (biggest != root) {
    std::swap(*(begin + root), *(begin + biggest));
    T swap = *(begin + root);
    *(begin + root) = *(begin + biggest);
    *(begin + biggest) = swap;
    SiftDown(begin, end, biggest, size);
  }
}

template <typename T>
void MakeHeap(const T begin, const T end) {
  int size = end - begin;
  for (int i = size / 2 - 1; i >= 0; --i) {
    SiftDown(begin, end, i, size);
  }
}

template <typename T>
void SortHeap(const T begin, const T end) {
  int size = end - begin;
  MakeHeap(begin, end);
  for (int i = size - 1; i > 0; --i) {
    T swap = *begin;
    *begin = *(begin + i);
    *(begin + i) = swap;
    SiftDown(begin, end, 0, i);
  }
}

#endif

int main() {
    int n;
    std::cin >> n;

    int arr[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    SortHeap(arr, arr + n);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}


