//
// Created by David Davitadze on 28/03/2019.
//

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>

class Matrix {
 private:
  size_t rows_;
  size_t columns_;

  std::vector<std::vector<int>> data_;

 public:
  Matrix(const size_t rows, const size_t columns);
  Matrix(const size_t rows, const size_t columns, const int value);

  Matrix(const Matrix& matrix) = default;

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

  std::vector<int>& operator[] (const size_t row);
  const std::vector<int>& operator[] (const size_t row) const;

  size_t getRows() const;
  size_t getColumns() const;
};

#endif // MATRIX_HPP_
