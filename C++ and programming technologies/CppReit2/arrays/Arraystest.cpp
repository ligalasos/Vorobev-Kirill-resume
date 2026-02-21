#include <iostream>

// Операция [] для доступа к элементу массива по индексу;
// Методы Front() и Back() для доступа к первому и последнему элементу соответственно;
// Метод Data(), возвращающий указатель на начало массива;
// Метод Size(), возвращающий размер массива;
// Метод Empty(), возвращающий true, если массив пуст, и false в противном случае;
// Метод Fill(const T& value), который заполняет массив значениями value;
// Метод Swap(Array<T, N>& other), обменивающий содержимое массивов одинакового размера.

template <class T, size_t N>
class Array {
 public:
  T array[N];

  T& operator[](size_t i) {
    return array[i];
  }

  T& Front() {
    return array[0];
  }

  T& Back() {
    return array[N - 1];
  }

  T* Data() {
    return array;
  }

  size_t Size() {
    return N;
  }

  bool Empty() {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T swap = this->array[i];
      this->array[i] = other.array[i];
      other.array[i] = swap;
    }
  }

  const T& operator[](size_t i) const {
    return array[i];
  }

  const T& Front() const {
    return array[0];
  }

  const T& Back() const {
    return array[N - 1];
  }

  const T* Data() const {
    return array;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }
};

// GetSize(array) должна возвращать число элементов в массиве array и 0, если array не является C-style массивом
// GetRank(array) должна возвращать число координат многомерного массива array
// GetNumElements(array) должна возвращать общее число элементов в многомерном массиве array

template <class T, size_t N>
size_t GetSize(const Array<T, N>& array) {
  return array.Size();
}

template <class T, size_t N>
size_t GetSize(T (*array)[N]) {
  return N;
}

template <class T>
size_t GetSize(T) {
  return 0;
}

template <class T, size_t N>
size_t GetRank(const Array<T, N>& array) {
  return array.Size();
}

template <class T, size_t N>
size_t GetNumElements(Array<T, N>& array) {
  return GetNumElements(array[0]) * N;
}

template <class T, class N>
size_t GetNumElements(T) {
  return 1;
}

int main() {
  Array<int, 2> arr{1, 2};
  Array<Array<int, 2>, 4> arr2{arr, arr, arr, arr};
  Array<Array<int, 0>, 0> arr3{};
  Array<Array<int, 4>, 10> arr4{};
  std::cout << GetNumElements(arr2);
}