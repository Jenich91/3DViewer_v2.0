#include <QApplication>
#include <QIcon>

#include "Controller/controller.h"
#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon(SRCDIR "etc/icon.png"));

  s21::Object model;
  s21::Controller controller(&model);
  s21::View w(&controller);

  w.setWindowTitle("3DViewer_v2.0");
  w.show();

  return a.exec();
}
