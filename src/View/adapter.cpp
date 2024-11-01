#include "adapter.h"

namespace s21 {
QVector<GLuint> Adapter::AdaptPolygon(Polygon* polygon) {
  auto poly_p = polygon->GetPolygon();
  return QVector<GLuint>{poly_p->begin(), poly_p->end()};
}

QVector<QVector3D> Adapter::AdaptMatrix(Matrix3D* matrix) {
  QVector<QVector3D> result_convert;
  for (uint i = 0; i < matrix->GetRowV(); ++i) {
    result_convert.push_back(QVector3D(matrix->operator()(i, 0),
                                       matrix->operator()(i, 1),
                                       matrix->operator()(i, 2)));
  }
  return result_convert;
}

QMatrix4x4 Adapter::AdaptMvpMatrix(
    const std::vector<std::vector<double>>& mvp_matrix) {
  QMatrix4x4 result_convert;
  for (uint i = 0; i < 4; ++i) {
    result_convert.setRow(
        i, QVector4D{float(mvp_matrix[i][0]), float(mvp_matrix[i][1]),
                     float(mvp_matrix[i][2]), float(mvp_matrix[i][3])});
  }

  return result_convert;
}
}  // namespace s21
