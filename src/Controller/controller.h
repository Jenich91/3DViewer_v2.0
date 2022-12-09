#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_
#include "../Model/object.h"

namespace s21 {
class Controller {
 private:
  s21::Object *object_;

 public:
  explicit Controller(s21::Object *obj) : object_{obj} {}

  Controller &operator=(const Controller &other) = delete;
  Controller &operator=(Controller &&other) = delete;
  Controller(const Controller &other) = delete;
  Controller(Controller &&other) = delete;

  void Parsing(std::string file) { object_->Parsing(file); }
  Polygon *GetPolygon() { return object_->GetPolygon(); }
  Matrix3D *GetMatrix() { return object_->GetMatrix(); }
  const auto &GetTransformMatrix() { return object_->GetTransformMatrix(); }

  auto GetFacetsCount() { return object_->GetFacetsCount(); }
  auto GetVertexCount() { return object_->GetVertexCount(); }

  void Rotation(double value, int asix) { object_->Rotation(value, asix); }
  void Move(double value, int asix) { object_->Move(value, asix); }
};
}  // namespace s21

#endif  // SRC_CONTROLLER_H_
