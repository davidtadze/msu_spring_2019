//
// Created by David Davitadze on 28/03/2019.
//

#include <vector>
#include <cassert>
#include <stdexcept>
#include <iostream>

#include "Matrix.h"

Matrix::Column::Column(const size_t arr)
  : column_(arr) {}

Matrix::Column::Column(const size_t arr, const int value)
  : column_(arr, value) {}

int& Matrix::Column::operator[] (const size_t index) {
  return column_.at(index);
}

const int& Matrix::Column::operator[] (const size_t index) const {
  return column_.at(index);
}

Matrix::Matrix(const size_t rows, const size_t columns)
  : rows_(rows)
  , columns_(columns)
  , data_(rows_, Column(columns_)) {}

Matrix::Matrix(const size_t columns, const size_t rows, const int value)
  : rows_(rows)
  , columns_(columns)
  , data_(rows_, Column(columns_, value)) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<int>> init_list) {
  rows_ = init_list.size();

#ifndef NDEBUG
  bool first = true;
  for(auto cur_column : init_list) {
    if(first) {
      columns_ = cur_column.size();
      first = false;
    }
    assert(cur_column.size() == columns_);
  }
#endif

  data_ = std::vector<Column>(rows_, Column(columns_));

  auto cur_row = init_list.begin();
  for (size_t y = 0; y < columns_; y++ , cur_row++) {
    auto cur_column = (*cur_row).begin();
    for (size_t x = 0; x < rows_; x++ , cur_column++) {
      data_[y][x] = *cur_column;
    }
  }
}

void Matrix::Dump() {
  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      std::cout << data_[y][x] << " ";
    }

    std::cout << "\n\n";
  }
}

bool Matrix::operator==(const Matrix& matrix) const {
  if(matrix.rows_ != rows_ || matrix.columns_ != columns_)
    return false;

  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      if(data_[y][x] != matrix.data_[y][x]) {
        return false;
      }
    }
  }

  return true;
}

bool Matrix::operator!=(const Matrix& matrix) const {
  return !operator==(matrix);
}

Matrix& Matrix::operator+=(const Matrix& matrix) {
  if(matrix.columns_ != columns_ || matrix.rows_ != rows_)
    throw std::runtime_error("matrix dimensions do not match");

  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      data_[y][x] += matrix.data_[y][x];
    }
  }

  return *this;
}

Matrix Matrix::operator+(const Matrix& matrix) const {
  if(matrix.columns_ != columns_ || matrix.rows_ != rows_)
    throw std::runtime_error("matrix dimensions do not match");

  Matrix tmp_matrix = *this;
  return tmp_matrix += matrix;
}

Matrix& Matrix::operator+=(const int scalar) {
  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      data_[y][x] += scalar;
    }
  }

  return *this;
}

Matrix Matrix::operator+(const int scalar) const {
  Matrix tmp_matrix = *this;
  return tmp_matrix += scalar;
}

Matrix& Matrix::operator*=(const Matrix& matrix) {
  if(columns_ != matrix.rows_ )
    throw std::runtime_error("matrix dimensions do not match");

  Matrix tmp_matrix(matrix.columns_, rows_, 0 );

  for (size_t y = 0; y < tmp_matrix.rows_; y++) {
    for (size_t x = 0; x < tmp_matrix.columns_; x++) {
      for (size_t i = 0; i < columns_; i++) {
        tmp_matrix.data_[y][x] += matrix.data_[y][i] * data_[i][x];
      }
    }
  }

  *this = tmp_matrix;
  return *this;
}

Matrix Matrix::operator*(const Matrix& matrix) const {
  Matrix tmp_matrix = *this;
  return tmp_matrix *= matrix;
}

Matrix& Matrix::operator*=(const int scalar) {
  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      data_[y][x] *= scalar;
    }
  }

  return *this;
}

Matrix Matrix::operator*(const int scalar) const {
  Matrix tmp_matrix = *this;
  return tmp_matrix *= scalar;
}

Matrix& Matrix::operator/=(const int scalar) {
  for (size_t y = 0; y < rows_; y++) {
    for (size_t x = 0; x < columns_; x++) {
      data_[y][x] /= scalar;
    }
  }

  return *this;
}

Matrix Matrix::operator/(const int scalar) const {
  Matrix tmp_matrix = *this;
  return tmp_matrix /= scalar;
}

Matrix::Column& Matrix::operator[](const size_t row) {
  if(row >= rows_) {
    throw std::out_of_range("expected row < matrix.rows_");
  }

  return data_[row];
}

const Matrix::Column& Matrix::operator[](const size_t row) const {
  if(row >= rows_) {
    throw std::out_of_range("expected row < matrix.rows_");
  }

  return data_[row];
}

size_t Matrix::getColumns() const {
  return columns_;
}
size_t Matrix::getRows() const {
  return rows_;
}
