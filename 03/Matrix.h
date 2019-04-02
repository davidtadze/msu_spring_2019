//
// Created by David Davitadze on 28/03/2019.
//

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>

class Matrix {
 private:
  struct Column {
    std::vector<int> column_;

    Column(const size_t arr);
    Column(const size_t arr, const int value);

    int& operator[] (const size_t index);
    const int& operator[] (const size_t index) const;
  };

  size_t rows_;
  size_t columns_;

  std::vector<Column> data_;

 public:
  Matrix(const size_t rows, const size_t columns);
  Matrix(const size_t rows, const size_t columns, const int value);

  Matrix(std::initializer_list<std::initializer_list<int>> init_list);

  void Dump();

  Matrix& operator=(const Matrix& matrix) = default;

  bool operator==(const Matrix& matrix) const;
  bool operator!=(const Matrix& matrix) const;

  Matrix& operator+=(const Matrix& matrix);
  Matrix  operator+ (const Matrix& matrix) const;

  Matrix& operator+=(const int scalar);
  Matrix  operator+ (const int scalar) const;

  Matrix& operator*=(const Matrix& matrix);
  Matrix  operator* (const Matrix& matrix) const;

  Matrix& operator*=(const int scalar);
  Matrix  operator* (const int scalar) const;

  Matrix& operator/=(const int scalar);
  Matrix  operator/ (const int scalar) const;

  Column& operator[] (const size_t row);
  const Column& operator[] (const size_t row) const;

  size_t getRows() const;
  size_t getColumns() const;
};

#endif // MATRIX_HPP_
