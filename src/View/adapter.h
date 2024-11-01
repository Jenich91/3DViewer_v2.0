#ifndef ADAPTER_H
#define ADAPTER_H
#include <Model/object.h>

#include <QMatrix4x4>
#include <QVector>

#include "OpenGL/gltypes.h"
#include "QtGui/qvectornd.h"

namespace s21 {
// Паттерн адаптер: преобразует интерфейс одного класса в другой интерфейс, на
// который рассчитаны клиенты
class Adapter {
 public:
  Adapter(){};
  QVector<GLuint> AdaptPolygon(Polygon *);
  QVector<QVector3D> AdaptMatrix(Matrix3D *);
  QMatrix4x4 AdaptMvpMatrix(const std::vector<std::vector<double>> &);

  Adapter &operator=(const Adapter &other) = delete;
  Adapter &operator=(Adapter &&other) = delete;
  Adapter(const Adapter &other) = delete;
  Adapter(Adapter &&other) = delete;
};
}  // namespace s21
#endif  // ADAPTER_H
