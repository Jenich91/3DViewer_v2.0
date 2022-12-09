#include "matrix.h"

namespace s21 {
// Default Constructor
Matrix::Matrix() {
  rows = 0;
  cols = 0;
}

// (Virtual) Destructor
Matrix::~Matrix() {}

// Access the individual elements
double &Matrix::operator()(const unsigned &row, const unsigned &col) {
  return this->mat[row][col];
}

// Access the individual elements (const)
const double &Matrix::operator()(const unsigned &row,
                                 const unsigned &col) const {
  return this->mat[row][col];
}

// Get the number of rows of the matrix
unsigned Matrix::get_rows() const { return this->rows; }

// Get the number of columns of the matrix
unsigned Matrix::get_cols() const { return this->cols; }

void Matrix::set_rows(unsigned new_value) { rows = new_value; }
void Matrix::set_cols(unsigned new_value) { cols = new_value; }

void Matrix::resize(unsigned new_rows, unsigned new_cols) {
  mat.resize(new_rows);
  for (unsigned i = 0; i < mat.size(); i++) {
    mat[i].resize(new_cols, 0.0f);
  }
  rows = new_rows;
  cols = new_cols;
}

}  // namespace s21
