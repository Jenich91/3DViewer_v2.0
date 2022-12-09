include(./QtGifImage/gifimage/qtgifimage.pri)
QT       += core gui opengl openglwidgets

# RC_ICONS = 3d_viewer_icon.ico
# ICON = 3d_viewer_icon.icns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Model/matrix.cc \
    Model/object.cc \
    Model/transform_matrix.cc \
    View/adapter.cpp \
    View/geometryengine.cpp \
    View/glwidget.cpp \
    View/main.cpp \
    View/settings.cc \
    View/view.cpp


HEADERS += \
    Controller/controller.h \
    Model/constant.h \
    Model/matrix.h \
    Model/object.h \
    Model/transform_matrix.h \
    View/adapter.h \
    View/geometryengine.h \
    View/glwidget.h \
    View/settings.h \
    View/view.h

FORMS += \
    View/view.ui

win32:LIBS += -lglu32 -lopengl32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    etc/Documentation.texi \
    etc/settings_demo.ini
    3rdparty/qtgifimage/src/gifimage/qtgifimage.pri \

DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += BUILD=\\\"$$PWD/../Build\\\"

RESOURCES += \
    Shaders/shaders.qrc

DESTDIR=$${BUILD}
OBJECTS_DIR=$${BUILD}
MOC_DIR=$${BUILD}
