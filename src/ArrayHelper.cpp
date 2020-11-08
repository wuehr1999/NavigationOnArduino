#include "ArrayHelper.h"

template <typename T> Array2D<T>::Array2D(int *xLengths, int yLength) {
  lengths = new int[yLength];

  int arrayLength = 0;

  this->yLength = yLength;

  for (int y = 0; y < yLength; y++) {
    lengths[y] = xLengths[y];
    arrayLength += xLengths[y];
  }

  array = new T[arrayLength];
}

template <typename T> Array2D<T>::~Array2D() {
  delete[] lengths;
  delete[] array;
}

template <typename T> bool Array2D<T>::set(int x, int y, const T &value) {
  if (y < yLength && x < lengths[y]) {
    int offset = x;
    for (int i = 0; i < y; i++) {
      offset += lengths[y];
    }

    array[offset] = value;

    return true;
  } else {
    return false;
  }
}

template <typename T> T Array2D<T>::get(int x, int y) const {
  int offset = x;
  for (int i = 0; i < y; i++) {
    offset += lengths[y];
  }

  return array[offset];
}
