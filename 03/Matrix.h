//
// Created by David Davitadze on 28/03/2019.
//

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <vector>

class Matrix {
 private:
  struct Column {
    std::vector<double> column_;

    Column(const size_t arr);
    Column(const size_t arr, const double value);

    double& operator[] (const size_t index);
    const double& operator[] (const size_t index) const;
  };

  size_t rows_;
  size_t columns_;

  std::vector<Column> data_;

 public:
  Matrix(const size_t rows, const size_t columns);
  Matrix(const size_t rows, const size_t columns, const double value);

  Matrix(std::initializer_list<std::initializer_list<double>> init_list);

  void Dump();

  Matrix& operator=(const Matrix& matrix) = default;

  bool operator==(const Matrix& matrix) const;
  bool operator!=(const Matrix& matrix) const;

  Matrix& operator+=(const Matrix& matrix);
  Matrix  operator+ (const Matrix& matrix) const;

  Matrix& operator+=(const double scalar);
  Matrix  operator+ (const double scalar) const;

  Matrix& operator*=(const Matrix& matrix);
  Matrix  operator* (const Matrix& matrix) const;

  Matrix& operator*=(const double scalar);
  Matrix  operator* (const double scalar) const;

  Matrix& operator/=(const double scalar);
  Matrix  operator/ (const double scalar) const;

  Column& operator[] (const size_t row);
  const Column& operator[] (const size_t row) const;

  void deleteRow(size_t row_num);
  void deleteColumn(size_t col_num);

  size_t getRows() const;
  size_t getColumns() const;
};

#endif // MATRIX_HPP_
