#include <QGuiApplication>

#include "cubewindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CubeWindow window;
    window.show();

    return app.exec();
}

