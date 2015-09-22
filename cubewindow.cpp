#include <QString>
#include <QtMath>
#include <QDateTime>
#include <QGuiApplication>
#include <cmath>

#include "cubewindow.h"

#define FRONT_EXTENT -1.5f
#define BACK_EXTENT -2.5f
#define LEFT_EXTENT -0.5f
#define RIGHT_EXTENT 0.5f
#define TOP_EXTENT 0.5f
#define BOTTOM_EXTENT -0.5f
#define CUBE_VERTICES 4 * 36

const float ROTATION_TIME = 2.5f;

static GLfloat const triangleVertices[] = {
    -0.75f, 0.75f, -2.0f, 1.0f,
    -0.75f, -0.75f, -2.0f, 1.0f,
    0.75f, -0.75f, -2.0f, 1.0f
};

static GLfloat const colorData[] = {
    // Front face
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    // Left face
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    // Right face
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    // Back face
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    // Top face
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    // Bottom face
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,

    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f
};

// Cube's origin: (0, 0, -2)
static GLfloat cubeVertices[] = {
    // Front face
    LEFT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,

    LEFT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,

    // Left face
    LEFT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,

    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,

    // Right face
    RIGHT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,

    RIGHT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,

    // Back face
    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,

    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,

    // Top face
    LEFT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,
    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,

    LEFT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, TOP_EXTENT, FRONT_EXTENT, 1.0f,

    // Bottom face
    LEFT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
    LEFT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,

    LEFT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, BACK_EXTENT, 1.0f,
    RIGHT_EXTENT, BOTTOM_EXTENT, FRONT_EXTENT, 1.0f,
};

static const char* vertexShaderSrc =
        "#version 330\n"
        "attribute highp vec4 position;\n"
        "attribute highp vec4 color;\n"
        "out highp vec4 theColor;\n"
        "uniform mat4 perspectiveMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = perspectiveMatrix * position;\n"
        "   theColor = color;\n"
        "}\n";

static const char* fragmentShaderSrc =
        "#version 330\n"
        "in highp vec4 theColor;\n"
        "out highp vec4 outputColor;\n"
        "void main()\n"
        "{\n"
        "outputColor = 0.6f * theColor;\n"
        "}\n";

CubeWindow::CubeWindow(UpdateBehavior updateBehavior,
                       QWindow *parent) :
    QOpenGLWindow(updateBehavior, parent),
    m_lastFrameTime(-1),
    m_currentDirection(RIGHT)
{
    // Works only if VSync is supported on user's computer
    connect(&m_timer, SIGNAL(timeout()), SLOT(update()));
    m_timer.setInterval(0);
    m_timer.start();
}

void CubeWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void CubeWindow::initializeGL()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc);
    m_program->link();
    m_posAtr = m_program->attributeLocation("position");
    m_colorAtr = m_program->attributeLocation("color");
    m_perspectiveMatrixUniform = m_program->uniformLocation("perspectiveMatrix");

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRangef(0.0f, 1.0f);
}

void CubeWindow::paintGL()
{
    float timeSinceLastFrame;

    if (m_lastFrameTime == -1) {
        m_lastFrameTime = QDateTime::currentMSecsSinceEpoch();
        timeSinceLastFrame = 0;
    } else {
        qint64 timeNow = QDateTime::currentMSecsSinceEpoch();
        timeSinceLastFrame = timeNow - m_lastFrameTime;
        m_lastFrameTime = timeNow;
    }
    float rotationScale = timeSinceLastFrame / (ROTATION_TIME * 1000.0f);
    float xAngle = 0.0f, yAngle = 0.0f;

    switch(m_currentDirection) {
    case RIGHT:
        yAngle = rotationScale * 360.0f;
        break;
    case LEFT:
        yAngle = - rotationScale * 360.0f;
        break;
    case UP:
        xAngle = - rotationScale * 360.0f;
        break;
    case DOWN:
        xAngle = rotationScale * 360.0f;
        break;
    }

    QMatrix4x4 perspectiveMatrix;
    perspectiveMatrix.frustum(-0.75f, 0.75f, -0.75f, 0.75f, 1.0f, 3.0f);

    QMatrix4x4 matrix;
    matrix.translate(0, 0, -2);
    matrix.rotate(xAngle, 1.0f, 0.0f, 0.0f);
    matrix.rotate(yAngle, 0.0f, 1.0f, 0.0f);
    matrix.translate(0, 0, 2);
    for (int i = 0; i < CUBE_VERTICES; i += 4) {
        QVector4D vector(cubeVertices[i], cubeVertices[i + 1],
                cubeVertices[i + 2], cubeVertices[i + 3]);
        vector = matrix * vector;
        cubeVertices[i] = vector.x();
        cubeVertices[i + 1] = vector.y();
        cubeVertices[i + 2] = vector.z();
        cubeVertices[i + 3] = vector.w();
    }

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_program->setUniformValue(m_perspectiveMatrixUniform, perspectiveMatrix);

    m_program->enableAttributeArray(m_posAtr);
    m_program->setAttributeArray(m_posAtr, cubeVertices, 4);
    m_program->enableAttributeArray(m_colorAtr);
    m_program->setAttributeArray(m_colorAtr, colorData, 4);

    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

    m_program->disableAttributeArray(m_posAtr);
    m_program->disableAttributeArray(m_colorAtr);

    m_program->release();
}

void CubeWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case (Qt::Key_Escape):
        QGuiApplication::quit();
        break;
    case (Qt::Key_Right):
        m_currentDirection = RIGHT;
        break;
    case (Qt::Key_Left):
        m_currentDirection = LEFT;
        break;
    case (Qt::Key_Up):
        m_currentDirection = UP;
        break;
    case (Qt::Key_Down):
        m_currentDirection = DOWN;
        break;
    }
}
