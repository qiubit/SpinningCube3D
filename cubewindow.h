#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

class CubeWindow : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit CubeWindow(UpdateBehavior updateBehavior = NoPartialUpdate,
                        QWindow * parent = 0);
    //~CubeWindow();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    // virtual void paintOverGL();
    // virtual void paintUnderGL();
    virtual void resizeGL(int w, int h);

private:
    QOpenGLShaderProgram *m_program;
    GLuint m_posAtr;

signals:

public slots:
};

#endif // CUBEWINDOW_H
