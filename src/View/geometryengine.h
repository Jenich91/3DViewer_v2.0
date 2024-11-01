#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Controller/controller.h"
#include "adapter.h"
#include "settings.h"

class GeometryEngine : public QOpenGLFunctions {
 public:
  explicit GeometryEngine(s21::Controller *);
  virtual ~GeometryEngine();

  void init_object(QString);
  void draw_geometry(QOpenGLShaderProgram *);

 private:
  QOpenGLBuffer arrayBuf;
  QOpenGLBuffer indexBuf;

  s21::Controller *controller_;
  s21::Adapter *adapter_;

  QVector4D color_line;
  QVector4D color_vertex;

  uint vertex_size;
  uint vertex_type;

  void pointDraw(QOpenGLShaderProgram *);
  void load_setting();

 public slots:

  void set_color_vertex(QVector4D new_color_v) { color_vertex = new_color_v; }
  void set_color_line(QVector4D new_color_l) { color_line = new_color_l; }
  void set_vertex_size(uint new_vert_size) { vertex_size = new_vert_size; }
  void set_type_vertex(uint new_type) { vertex_type = new_type; }

  uint get_vertex_count() { return controller_->GetVertexCount(); }
  uint get_facets_count() { return controller_->GetFacetsCount(); }
  QVector4D get_color_vertex() { return color_vertex; }
  QVector4D get_color_line() { return color_line; }
};
#endif  // GEOMETRYENGINE_H
