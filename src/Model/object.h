#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <math.h>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include "constant.h"
#include "matrix.h"
#include "transform_matrix.h"

namespace sfleta {
class Matrix3D : protected Matrix {
 private:
  Matrix* vertices_;
  size_t row_v_;

 public:
  Matrix3D() : vertices_{new Matrix()}, row_v_{0} {}
  ~Matrix3D() { delete vertices_; };

  Matrix3D& operator=(const Matrix3D& other) = delete;
  Matrix3D& operator=(Matrix3D&& other) = delete;
  Matrix3D(const Matrix3D& other) = delete;
  Matrix3D(Matrix3D&& other) = delete;

  inline unsigned GetRowV() { return row_v_; }
  inline void SetRowV(size_t new_row) { row_v_ = new_row; }
  inline double& operator()(int i, int j) {
    return vertices_->operator()(i, j);
  }

  void ParseVLine(char*);
  inline void Resize(unsigned size) { vertices_->resize(size, 3); }
};

class Polygon {
 private:
  std::vector<int>* polygons_{};

 public:
  Polygon() : polygons_(new std::vector<int>) {}
  ~Polygon() { delete polygons_; }

  Polygon& operator=(const Polygon& other) {
    polygons_ = other.polygons_;
    return *this;
  }
  Polygon& operator=(Polygon&& other) = delete;
  Polygon(const Polygon& other) { *this = other; }
  Polygon(Polygon&& other) = delete;

  void ParseFLine(char*);
  inline size_t GetSize() { return polygons_->size(); }
  inline int& operator()(int i) { return polygons_->at(i); }
  inline void Resize(unsigned size) { polygons_->reserve(size); }
  inline auto GetPolygon() { return polygons_; }
};

// Паттерн фасад: предоставляет унифицированный интерфейс вместо набора
// интерфейсов некоторой подсистемы
class Object {
 private:
  Matrix3D* matrix_;
  Polygon* polygon_;
  Matrix4D* transform_matrix_;

  void InitObjects(const char*);
  void FillObjects(const char*);
  void CreateTransfomMatrix();
  double MaxNumber(double num1, double num2);

 public:
  Object()
      : matrix_{nullptr}, polygon_{nullptr}, transform_matrix_{new Matrix4D} {}
  ~Object() {
    delete polygon_;
    delete matrix_;
    delete transform_matrix_;
  };

  Object& operator=(const Object& other) = delete;
  Object& operator=(Object&& other) = delete;
  Object(const Object& other) = delete;
  Object(Matrix3D&& other) = delete;

  inline int& GetFacetsElem(int i) { return polygon_->operator()(i); }
  inline double& GetVertexElem(int i, int j) {
    return matrix_->operator()(i, j);
  }

  inline size_t GetVertexCount() { return matrix_->GetRowV(); }
  inline size_t GetFacetsCount() { return polygon_->GetSize(); }

  Polygon* GetPolygon() { return polygon_; }
  Matrix3D* GetMatrix() { return matrix_; }
  const auto& GetTransformMatrix() {
    return transform_matrix_->GetTransformMatrix();
  }

  void Rotation(double value, int asix) {
    transform_matrix_->Rotate(value, asix);
  }
  void Move(double value, int asix) { transform_matrix_->Move(value, asix); }

  void Parsing(std::string);
};
}  // namespace sfleta
#endif  // SRC_MODEL_H_
