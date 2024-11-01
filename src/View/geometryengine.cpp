#include "geometryengine.h"

struct VertexData {
  QVector3D position;
  QVector2D texCoord;
};

GeometryEngine::GeometryEngine(s21::Controller* c)
    : indexBuf(QOpenGLBuffer::IndexBuffer),
      controller_{c},
      adapter_{new s21::Adapter},
      color_line{0.5, 0.5, 0.5, 1.0},
      color_vertex{0.8, 0.8, 0.8, 1.0} {
  initializeOpenGLFunctions();
}

GeometryEngine::~GeometryEngine() {
  arrayBuf.destroy();
  indexBuf.destroy();
  delete adapter_;
}

void GeometryEngine::init_object(QString file_path) {
  arrayBuf.create();
  indexBuf.create();

  controller_->Parsing(file_path.toStdString());

  QVector<QVector3D> vertices{adapter_->AdaptMatrix(controller_->GetMatrix())};

  arrayBuf.bind();
  arrayBuf.allocate(vertices.data(), sizeof(QVector3D) * vertices.length());

  QVector<GLuint> indices{adapter_->AdaptPolygon(controller_->GetPolygon())};

  indexBuf.bind();
  indexBuf.allocate(indices.data(), sizeof(GLuint) * indices.length());

  load_setting();
}

void GeometryEngine::draw_geometry(QOpenGLShaderProgram* program) {
  if (!arrayBuf.isCreated()) return;

  arrayBuf.bind();
  indexBuf.bind();

  int vertexLocation = program->attributeLocation("a_position");
  program->enableAttributeArray(vertexLocation);
  program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3,
                              sizeof(QVector3D));

  program->setUniformValue("color", color_line);

  glDrawElements(GL_LINES, controller_->GetFacetsCount(), GL_UNSIGNED_INT,
                 nullptr);

  if (vertex_type) pointDraw(program);
}

void GeometryEngine::pointDraw(QOpenGLShaderProgram* program) {
  program->setAttributeValue("size", vertex_size);
  vertex_type == 2 ? glEnable(GL_POINT_SMOOTH) : glDisable(GL_POINT_SMOOTH);

  program->setUniformValue("color", color_vertex);
  glDrawElements(GL_POINTS, controller_->GetFacetsCount(), GL_UNSIGNED_INT,
                 nullptr);
}

void GeometryEngine::load_setting() {
  QSettings _settings(SRCDIR "etc/config.ini", QSettings::IniFormat);

  double colorR = _settings.value("LineColorW", 0.0).toDouble();
  double colorG = _settings.value("LineColorX", 0.0).toDouble();
  double colorB = _settings.value("LineColorY", 0.0).toDouble();
  double colorA = _settings.value("LineColorZ", 1.0).toDouble();

  double _colorR = _settings.value("VertexColorW", 0.0).toDouble();
  double _colorG = _settings.value("VertexColorX", 0.0).toDouble();
  double _colorB = _settings.value("VertexColorY", 0.0).toDouble();
  double _colorA = _settings.value("VertexColorZ", 1.0).toDouble();

  set_color_line(QVector4D(colorR, colorG, colorB, colorA));
  set_color_vertex(QVector4D(_colorR, _colorG, _colorB, _colorA));

  uint vertex_size = _settings.value("VertexWidth", 0).toUInt();
  uint vertex_type = _settings.value("VertexType", 0).toUInt();

  set_vertex_size(vertex_size);
  set_type_vertex(vertex_type);
}
