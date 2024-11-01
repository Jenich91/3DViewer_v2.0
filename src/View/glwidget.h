#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QBasicTimer>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>

#include "geometryengine.h"

class QOpenGLShaderProgram;
class GeometryEngine;

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  GeometryEngine *geometries_;
  s21::Controller *controller_;
  s21::Adapter *adapter_;

  void setController(s21::Controller *c) { controller_ = c; }

 private:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int, int) override;

  void setTypeLine();
  void clean();

  QOpenGLShaderProgram program;
  bool dotted;
  bool projection_type;
  uint line_width;
  QVector4D color_back;

  QMatrix4x4 projection;

  QBasicTimer timer;
  QVector2D mousePressPosition;
  QVector3D rotationAxis;
  qreal angularSpeed;
  QQuaternion rotation;

  void mouseReleaseEvent(QMouseEvent *e) override;
  void mousePressEvent(QMouseEvent *e) override;
  void timerEvent(QTimerEvent *e) override;

 public slots:

  void set_color_back();
  void set_ortho_projection(bool);

  void set_line_width(uint new_width) {
    line_width = new_width;
    update();
  }
  void set_dotted_line(bool new_dotted) {
    dotted = new_dotted;
    update();
  }
  void set_solid_line(bool new_dotted) {
    dotted = !new_dotted;
    update();
  }
  void load_color_back(QVector4D color) {
    color_back = color;
    update();
  }

  void set_perspective_projection(bool new_projection) {
    projection_type = !new_projection;
    resizeGL(width(), height());
    update();
  }

  QVector4D get_color_back() { return color_back; }
};

#endif  // GLWIDGET_H
