#include "transform_matrix.h"

#include <cmath>

namespace sfleta {
Matrix4D::Matrix4D(double scale, double y)
    : normal_scale_{scale}, normal_y_{y} {
  SetToIdentity(&rotate_x_);
  SetToIdentity(&rotate_y_);
  SetToIdentity(&rotate_z_);
  SetToIdentity(&move_);

  move_[1][3] = -normal_y_;
  move_[3][3] = normal_scale_;
}

Matrix4D::~Matrix4D() {}

void Matrix4D::SetToIdentity(matrix4d* matrix) {
  *matrix = matrix4d{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
}

Matrix4D::matrix4d operator*(const Matrix4D::matrix4d& first,
                             const Matrix4D::matrix4d& second) {  // fixed
  Matrix4D::matrix4d result{
      {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  for (unsigned i = 0; i < 4; i++) {
    for (unsigned j = 0; j < 4; j++) {
      for (unsigned k = 0; k < 4; k++) {
        result[i][j] += first[i][k] * second[k][j];
      }
    }
  }

  return result;
}

void Matrix4D::Rotate(double value, int asix) {
  if (asix == X) {
    rotate_x_[1] = {0, cos(value), sin(value), 0};
    rotate_x_[2] = {0, -sin(value), cos(value), 0};
  } else if (asix == Y) {
    rotate_y_[0] = {cos(value), 0, -sin(value), 0};
    rotate_y_[2] = {sin(value), 0, cos(value), 0};
  } else if (asix == Z) {
    rotate_z_[0] = {cos(value), sin(value), 0, 0};
    rotate_z_[1] = {-sin(value), cos(value), 0, 0};
  }
}

void Matrix4D::Move(double value, int asix) {
  if (asix == X) {
    move_[0][3] = value;
  } else if (asix == Y) {
    move_[1][3] = value - normal_y_;
  } else if (asix == Z) {
    move_[2][3] = value;
  } else {
    move_[3][3] = value * normal_scale_;
  }
}

Matrix4D::matrix4d&& Matrix4D::GetTransformMatrix() {
  transform_ = matrix4d{rotate_x_ * rotate_y_ * rotate_z_ * move_};
  return std::move(transform_);
}
}  // namespace sfleta
