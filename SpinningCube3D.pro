TEMPLATE = app

QT += gui
CONFIG += c++11

SOURCES += src/main.cpp \
    src/cubewindow.cpp

RESOURCES +=

# Default rules for deployment.
include(SpinningCube3D.pri)

HEADERS += \
    src/cubewindow.h

