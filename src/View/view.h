#ifndef VIEW_H
#define VIEW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>
#include <QToolTip>

#include "glwidget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT
 public:
  explicit View(s21::Controller *, QWidget *parent = nullptr);
  ~View();

 private:
  bool chooseFileDestiny();
  QString SelectDir();
  void showSavedToolTip();
  void showGifToolTip(unsigned second);
  void set_start_value_slider();
  void setConnect();

  void ViewNewFile(QString);
  void keyPressEvent(QKeyEvent *);

 private slots:
  void MakeScreenshot();
  void MakeGif();
  void RecordGif();

  void on_pushButton_save_clicked();
  void on_pushButton_load_clicked();
  void on_pushButton_close_clicked();
  void on_pushButton_openFile_clicked();

  void on_horizontalSlider_X_rotation_valueChanged(int);
  void on_horizontalSlider_Y_rotation_valueChanged(int);
  void on_horizontalSlider_Z_rotation_valueChanged(int);

  void on_horizontalSlider_X_move_valueChanged(int);
  void on_horizontalSlider_Y_move_valueChanged(int);
  void on_horizontalSlider_Z_move_valueChanged(int);
  void on_horizontalSlider_scale_valueChanged(int);

  void on_pushButton_VertexColor_clicked();
  void on_pushButton_LineColor_clicked();

  void on_comboBox_VertexType_currentIndexChanged(int);
  void on_spinBox_VertexWidth_valueChanged(int);

  void on_doubleSpinBox_scale_valueChanged(double arg1);

 private:
  Ui::View *ui;
  s21::Controller *controller_;
  QStringList models_;

  struct gif {
    QGifImage *gif_obj;
    QTimer *timer;
    unsigned timerCounter;
  } g;
  QString path;
};
}  // namespace s21
#endif  // VIEW_H
