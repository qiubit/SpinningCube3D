TEMPLATE = app

QT += gui
CONFIG += c++11

SOURCES += main.cpp \
    cubewindow.cpp

RESOURCES +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    cubewindow.h

