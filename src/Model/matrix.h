#ifndef SRC_MATRIX_OOP_H_
#define SRC_MATRIX_OOP_H_
#include <vector>

namespace sfleta {
class Matrix {
 private:
  std::vector<std::vector<double>> mat;
  unsigned rows;
  unsigned cols;

 public:
  Matrix();
  virtual ~Matrix();

  Matrix &operator=(const Matrix &other) = delete;
  Matrix &operator=(Matrix &&other) = delete;
  Matrix(const Matrix &other) = delete;
  Matrix(Matrix &&other) = delete;

  // Access the individual elements
  double &operator()(const unsigned &row, const unsigned &col);
  const double &operator()(const unsigned &row, const unsigned &col) const;

  // Access the row and column sizes
  unsigned get_rows() const;
  unsigned get_cols() const;

  void set_rows(unsigned new_value);
  void set_cols(unsigned new_value);
  void resize(unsigned new_rows, unsigned new_cols);
};
}  // namespace sfleta

#endif  // SRC_MATRIX_OOP_H_
