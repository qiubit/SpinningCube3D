#include <QGuiApplication>
#include <QSurfaceFormat>

#include "cubewindow.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CubeWindow window;
    window.resize(400, 400);
    window.show();

    return app.exec();
}

