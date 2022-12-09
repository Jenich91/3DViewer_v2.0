#ifndef SRC_MVP_MATRIX_H_
#define SRC_MVP_MATRIX_H_

#include <vector>

#include "constant.h"

namespace s21 {
class Matrix4D {
 public:
  using matrix4d = std::vector<std::vector<double>>;

 private:
  matrix4d move_;
  matrix4d rotate_x_;
  matrix4d rotate_y_;
  matrix4d rotate_z_;

  double normal_scale_;
  double normal_y_;

  matrix4d transform_;

  void SetToIdentity(matrix4d *);

 public:
  Matrix4D(double scale = 1., double y = 0.);
  ~Matrix4D();

  Matrix4D &operator=(const Matrix4D &other) = delete;
  Matrix4D &operator=(Matrix4D &&other) = delete;
  Matrix4D(const Matrix4D &other) = delete;
  Matrix4D(Matrix4D &&other) = delete;

  friend matrix4d operator*(const matrix4d &, const matrix4d &);

  matrix4d &&GetTransformMatrix();
  void Rotate(double, int);
  void Move(double, int);
};

}  // namespace s21

#endif  // SRC_MVP_MATRIX_H_
