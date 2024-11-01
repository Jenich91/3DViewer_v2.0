#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      geometries_{nullptr},
      controller_{nullptr},
      dotted{false},
      projection_type{false},
      color_back{1.0, 1.0, 1.0, 1.0} {}

GLWidget::~GLWidget() { clean(); }

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();

  glClearColor(color_back.x(), color_back.y(), color_back.z(), color_back.w());
  glClear(GL_COLOR_BUFFER_BIT);

  program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                  SRCDIR "Shaders/v_shader.glsl");
  program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                  SRCDIR "Shaders/f_shader.glsl");
  program.link();
  program.bind();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PROGRAM_POINT_SIZE);

  geometries_ = new GeometryEngine(controller_);
  timer.start(12, this);
}

void GLWidget::resizeGL(int w, int h) {
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  const qreal zNear = 0.01, zFar = 100, fov = 45.0;

  projection.setToIdentity();
  if (projection_type) {
    const double rect = 1.0;
    projection.ortho(-rect * aspect, rect * aspect, -rect, rect, zNear, zFar);
  } else {
    projection.perspective(fov, aspect, zNear, zFar);
  }
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(color_back.x(), color_back.y(), color_back.z(), color_back.w());
  glClear(GL_COLOR_BUFFER_BIT);

  glLineWidth(line_width);
  setTypeLine();

  QMatrix4x4 matrix_;
  matrix_.setToIdentity();
  matrix_.translate(0.0, 0.0, -2.5);
  matrix_.rotate(rotation);

  program.setUniformValue(
      "mvp_matrix",
      projection * matrix_ *
          adapter_->AdaptMvpMatrix(controller_->GetTransformMatrix()));
  geometries_->draw_geometry(&program);
}

void GLWidget::set_color_back() {
  QColor color = QColorDialog::getColor();
  color_back =
      QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF());
  update();
}

void GLWidget::set_ortho_projection(bool new_projection) {
  projection_type = new_projection;
  resizeGL(width(), height());
  update();
}

void GLWidget::setTypeLine() {
  dotted                        ? glEnable(GL_LINE_STIPPLE),
      glLineStipple(10, 0xAAAA) : glDisable(GL_LINE_STIPPLE);
}

void GLWidget::mousePressEvent(QMouseEvent* e) {
  mousePressPosition = QVector2D(e->position());
}

void GLWidget::mouseReleaseEvent(QMouseEvent* e) {
  QVector2D diff = QVector2D(e->position()) - mousePressPosition;
  QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();
  qreal acc = diff.length() / 100.0;
  rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();
  angularSpeed += acc;
}

void GLWidget::timerEvent(QTimerEvent*) {
  angularSpeed *= 0.99;
  if (angularSpeed < 0.01) {
    angularSpeed = 0.0;
  } else {
    rotation =
        QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;
    update();
  }
}

void GLWidget::clean() {
  makeCurrent();
  delete geometries_;
  doneCurrent();
}
