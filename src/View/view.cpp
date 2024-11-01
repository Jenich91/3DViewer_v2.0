#include "view.h"

#include "ui_view.h"

namespace s21 {
View::View(s21::Controller *c, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::View),
      controller_{c},
      models_{QDir(SRCDIR "obj_files/").entryList(QStringList() << "*.obj")} {
  ui->setupUi(this);
  ui->openGLWidget->setController(controller_);

  setConnect();
  on_pushButton_load_clicked();
}

void View::keyPressEvent(QKeyEvent *event) {
  static int model_index = 0;
  if (event->key() == Qt::Key_W) {
    ++model_index;
  } else if (event->key() == Qt::Key_S) {
    --model_index;
  } else return;

  if (model_index < 0) model_index = models_.size() - 1;

  ViewNewFile(SRCDIR "obj_files/" + models_[model_index % models_.size()]);
  ui->openGLWidget->update();
}

void View::setConnect() {
  connect(ui->radioButton_1_projection, &QPushButton::clicked, ui->openGLWidget,
          &GLWidget::set_perspective_projection);
  connect(ui->radioButton_2_projection, &QPushButton::clicked, ui->openGLWidget,
          &GLWidget::set_ortho_projection);
  connect(ui->pushButton_BackgroundColor, &QPushButton::clicked,
          ui->openGLWidget, &GLWidget::set_color_back);
  connect(ui->radioButton_LineType_2, &QRadioButton::clicked, ui->openGLWidget,
          &GLWidget::set_dotted_line);
  connect(ui->radioButton_LineType_1, &QRadioButton::clicked, ui->openGLWidget,
          &GLWidget::set_solid_line);
  connect(ui->spinBox_EdgesWidth, &QSpinBox::valueChanged, ui->openGLWidget,
          &GLWidget::set_line_width);

  connect(ui->spinBox_rotation_x, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_X_rotation_valueChanged);
  connect(ui->spinBox_rotation_y, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_Y_rotation_valueChanged);
  connect(ui->spinBox_rotation_z, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_Z_rotation_valueChanged);

  connect(ui->spinBox_move_x, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_X_move_valueChanged);
  connect(ui->spinBox_move_y, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_Y_move_valueChanged);
  connect(ui->spinBox_move_z, &QSpinBox::valueChanged, this,
          &View::on_horizontalSlider_Z_move_valueChanged);

  connect(ui->pushButton_SaveScreenshot, SIGNAL(clicked()), this,
          SLOT(MakeScreenshot()));
  connect(ui->pushButton_RecordGif, SIGNAL(clicked()), this, SLOT(MakeGif()));
}

void View::set_start_value_slider() {
  ui->horizontalSlider_X_move->setValue(0);
  ui->horizontalSlider_Y_move->setValue(0);
  ui->horizontalSlider_Z_move->setValue(0);
  ui->horizontalSlider_X_rotation->setValue(0);
  ui->horizontalSlider_Y_rotation->setValue(0);
  ui->horizontalSlider_Z_rotation->setValue(0);
  ui->horizontalSlider_scale->setValue(100.0);
}

View::~View() {
  on_pushButton_save_clicked();
  delete ui;
}

void View::on_pushButton_save_clicked() {
  SettingStruct settings_struct;
  settings_struct.IsCentral_projection =
      ui->radioButton_1_projection->isChecked();
  settings_struct.EdgesWidth = ui->spinBox_EdgesWidth->value();
  settings_struct.VertexWidth = ui->spinBox_VertexWidth->value();
  settings_struct.VertexType = ui->comboBox_VertexType->currentIndex();
  settings_struct.IsLineType1 = ui->radioButton_LineType_1->isChecked();
  settings_struct.IsPicType1 = ui->radioButton_jpeg->isChecked();
  settings_struct.BackgroundColor =
      QVector4D(ui->openGLWidget->get_color_back().x(),
                ui->openGLWidget->get_color_back().y(),
                ui->openGLWidget->get_color_back().z(),
                ui->openGLWidget->get_color_back().w());

  settings_struct.LineColor =
      QVector4D(ui->openGLWidget->geometries_->get_color_line().x(),
                ui->openGLWidget->geometries_->get_color_line().y(),
                ui->openGLWidget->geometries_->get_color_line().z(),
                ui->openGLWidget->geometries_->get_color_line().w());

  settings_struct.VertexColor =
      QVector4D(ui->openGLWidget->geometries_->get_color_vertex().x(),
                ui->openGLWidget->geometries_->get_color_vertex().y(),
                ui->openGLWidget->geometries_->get_color_vertex().z(),
                ui->openGLWidget->geometries_->get_color_vertex().w());

  Settings::GetInstance().SaveInFile(settings_struct);
}

void View::on_pushButton_load_clicked() {
  SettingStruct settings = Settings::GetInstance().LoadFromFile();

  bool projection = settings.IsCentral_projection;
  ui->radioButton_1_projection->setChecked(projection);
  ui->radioButton_2_projection->setChecked(!projection);
  ui->openGLWidget->set_ortho_projection(!projection);

  ui->spinBox_EdgesWidth->setValue(settings.EdgesWidth);
  ui->spinBox_VertexWidth->setValue(settings.VertexWidth);
  ui->comboBox_VertexType->setCurrentIndex(settings.VertexType);

  bool LineType = settings.IsLineType1;
  ui->radioButton_LineType_1->setChecked(LineType);
  ui->radioButton_LineType_2->setChecked(!LineType);
  ui->openGLWidget->set_dotted_line(!LineType);

  bool PicType = settings.IsPicType1;
  ui->radioButton_jpeg->setChecked(PicType);
  ui->radioButton_bmp->setChecked(!PicType);

  ui->openGLWidget->load_color_back(QVector4D(settings.BackgroundColor));
  if (ui->openGLWidget->geometries_) {
    ui->openGLWidget->geometries_->set_color_line(
        QVector4D(settings.LineColor));
    ui->openGLWidget->geometries_->set_color_vertex(
        QVector4D(settings.VertexColor));
  }
}

void View::on_pushButton_openFile_clicked() {
  QString filepath = QFileDialog::getOpenFileName(
      this, "Choose obj file", SRCDIR "/obj_files/", "*.obj");
  if (!filepath.isEmpty() && ui->openGLWidget->geometries_) {
    ViewNewFile(filepath);
  }
}

void View::ViewNewFile(QString filepath) {
  set_start_value_slider();
  ui->openGLWidget->geometries_->init_object(filepath);
  ui->label_VertexCount_value->setText(
      QString::number(ui->openGLWidget->geometries_->get_vertex_count()));
  ui->label_EdgesCount_value->setText(
      QString::number(ui->openGLWidget->geometries_->get_facets_count()));
  ui->label_fieldFilename->setText(QFileInfo(filepath).fileName());

  SettingStruct settings = Settings::GetInstance().LoadFromFile();
  if (ui->openGLWidget->geometries_) {
    ui->openGLWidget->geometries_->set_color_line(
        QVector4D(settings.LineColor));
    ui->openGLWidget->geometries_->set_color_vertex(
        QVector4D(settings.VertexColor));
  }
  ui->openGLWidget->update();
}

void View::on_pushButton_close_clicked() { close(); }

void View::on_horizontalSlider_X_rotation_valueChanged(int value) {
  ui->spinBox_rotation_x->setValue(value);
  ui->horizontalSlider_X_rotation->setValue(value);
  controller_->Rotation(value / 57., X);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_Y_rotation_valueChanged(int value) {
  ui->spinBox_rotation_y->setValue(value);
  ui->horizontalSlider_Y_rotation->setValue(value);
  controller_->Rotation(value / 57., Y);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_Z_rotation_valueChanged(int value) {
  ui->spinBox_rotation_z->setValue(value);
  ui->horizontalSlider_Z_rotation->setValue(value);
  controller_->Rotation(value / 57., Z);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_X_move_valueChanged(int value) {
  ui->spinBox_move_x->setValue(value);
  ui->horizontalSlider_X_move->setValue(value);
  controller_->Move(value / 7., X);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_Y_move_valueChanged(int value) {
  ui->spinBox_move_y->setValue(value);
  ui->horizontalSlider_Y_move->setValue(value);
  controller_->Move(value / 7., Y);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_Z_move_valueChanged(int value) {
  ui->spinBox_move_z->setValue(value);
  ui->horizontalSlider_Z_move->setValue(value);
  controller_->Move(value / 7., Z);
  ui->openGLWidget->update();
}

void View::on_horizontalSlider_scale_valueChanged(int value) {
  ui->doubleSpinBox_scale->setValue(value * 0.01);
  controller_->Move(1 / (value * 0.01), 3);
  ui->openGLWidget->update();
}

void View::on_pushButton_VertexColor_clicked() {
  QColor color = QColorDialog::getColor();
  ui->openGLWidget->geometries_->set_color_vertex(
      QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
  ui->openGLWidget->update();
}

void View::on_pushButton_LineColor_clicked() {
  QColor color = QColorDialog::getColor();
  ui->openGLWidget->geometries_->set_color_line(
      QVector4D(color.redF(), color.greenF(), color.blueF(), color.alphaF()));
  ui->openGLWidget->update();
}

void View::on_comboBox_VertexType_currentIndexChanged(int index) {
  if (ui->openGLWidget->geometries_) {
    ui->openGLWidget->geometries_->set_type_vertex(index);
    ui->openGLWidget->update();
  }
}

void View::on_spinBox_VertexWidth_valueChanged(int arg1) {
  if (ui->openGLWidget->geometries_) {
    ui->openGLWidget->geometries_->set_vertex_size(arg1);
    ui->openGLWidget->update();
  }
}

void View::on_doubleSpinBox_scale_valueChanged(double arg1) {
  ui->horizontalSlider_scale->setValue(arg1 * 100);
}

void View::MakeGif() {
  if (chooseFileDestiny()) {
    g = {new QGifImage, new QTimer, 0};
    connect(g.timer, SIGNAL(timeout()), this, SLOT(RecordGif()));
    g.timer->start(100);
  }
}

void View::RecordGif() {
  if (g.timerCounter % 10 == 0) {
    showGifToolTip(5 - (g.timerCounter / 10));
  }
  ++g.timerCounter;

  g.gif_obj->addFrame(ui->openGLWidget->grabFramebuffer(), 100);

  if (g.timerCounter == 50) {
    g.timer->stop();
    g.gif_obj->save(path + "/" + QDate::currentDate().toString() + " " +
                    QTime::currentTime().toString() + ".gif");
    delete g.gif_obj;
  }
}

void View::MakeScreenshot() {
  if (chooseFileDestiny()) {
    bool mode = ui->radioButton_jpeg->isChecked();
    QString EXT = mode ? "jpeg" : "bmp";
    ui->openGLWidget->grabFramebuffer().save(
        path + "/" + QDate::currentDate().toString() + " " +
        QTime::currentTime().toString() + "." + EXT);
    showSavedToolTip();
  }
}

bool View::chooseFileDestiny() {
  QString tmp_path = SelectDir();
  QFileInfo dir(tmp_path);
  if (dir.exists() && dir.isDir()) {
    path = tmp_path;
    return true;
  }
  return false;
}

void View::showGifToolTip(unsigned second) {
  auto tooltipPoint = ui->pushButton_RecordGif->mapToGlobal(QPoint());
  QToolTip::showText(tooltipPoint,
                     "Attention! Screen recording is in progress...\n" +
                         QString::number(second) + " seconds left");
}

void View::showSavedToolTip() {
  auto tooltipPoint = ui->pushButton_SaveScreenshot->mapToGlobal(QPoint());
  QToolTip::showText(tooltipPoint, "File saved success!");
}

QString View::SelectDir() {
  return QFileDialog::getExistingDirectory(
      this, QObject::tr("Open Directory"), SRCDIR "../",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
}
}  // namespace s21
