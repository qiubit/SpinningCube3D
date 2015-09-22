#ifndef CUBEWINDOW_H
#define CUBEWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QKeyEvent>

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
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    QOpenGLShaderProgram *m_program;
    GLuint m_posAtr;
    GLuint m_colorAtr;
    GLuint m_transformationMatrixUniform;
    QTimer m_timer;
    qint64 m_lastFrameTime;
    float m_currentXRotationAngle;
    float m_currentYRotationAngle;

    enum Direction {
        LEFT,
        RIGHT,
        DOWN,
        UP
    };
    Direction m_currentDirection;

signals:

public slots:
};

#endif // CUBEWINDOW_H
