#ifndef ARRAYHELPER_H
#define ARRAYHELPER_H

template <typename T> class Array2D {

private:
  T *array;

  int yLength;
  int *lengths;

public:
  Array2D(int *xLengths, int yLength);

  ~Array2D();

  bool set(int x, int y, const T &value);
  T get(int x, int y) const;
};
#endif
