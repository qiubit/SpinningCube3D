#include <QString>
#include <QtMath>
#include <QDateTime>
#include <cmath>

#include "cubewindow.h"

#define FRONT_EXTENT -1.5f
#define BACK_EXTENT -2.5f
#define LEFT_EXTENT -0.5f
#define RIGHT_EXTENT 0.5f
#define TOP_EXTENT 0.5f
#define BOTTOM_EXTENT -0.5f

const float ROTATION_TIME = 10.0f;

static GLfloat const triangleVertices[] = {
    -0.75f, 0.75f, -2.0f, 1.0f,
    -0.75f, -0.75f, -2.0f, 1.0f,
    0.75f, -0.75f, -2.0f, 1.0f
};

// Cube's origin: (0, 0, -2)
static GLfloat const cubeVertices[] = {
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
};

static const char* vertexShaderSrc =
        "#version 330\n"
        "layout(location = 0) in vec4 position;\n"
        "uniform mat4 transformationMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = transformationMatrix * position;\n"
        "}\n";

static const char* fragmentShaderSrc =
        "#version 330\n"
        "out vec4 outputColor;\n"
        "void main()\n"
        "{\n"
        "float lerpValue = gl_FragCoord.y / 500.0f;\n"
        "outputColor = mix(vec4(1.0f, 1.0f, 1.0f, 1.0f),\n"
        "                  vec4(0.2f, 0.2f, 0.2f, 1.0f), lerpValue);\n"
        "}\n";

CubeWindow::CubeWindow(UpdateBehavior updateBehavior,
                       QWindow *parent) :
    QOpenGLWindow(updateBehavior, parent),
    m_lastFrameTime(-1),
    m_currentXRotationAngle(0.0f),
    m_currentYRotationAngle(0.0f)
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
    m_transformationMatrixUniform = m_program->uniformLocation("transformationMatrix");
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

    m_currentYRotationAngle =
            fmod(m_currentYRotationAngle + rotationScale * 360.0f, 360.0f);

    QMatrix4x4 matrix;
    matrix.frustum(-1, 1, -1, 1, 1, 3);
    matrix.translate(0, 0, -2);
    matrix.rotate(m_currentYRotationAngle, 0.0f, 1.0f, 0.0f);
    matrix.translate(0, 0, 2);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();
    m_program->setUniformValue(m_transformationMatrixUniform, matrix);

    m_program->enableAttributeArray(m_posAtr);
    m_program->setAttributeArray(m_posAtr, cubeVertices, 4);

    glDrawArrays(GL_TRIANGLES, 0, 3 * 6);

    m_program->disableAttributeArray(m_posAtr);

    m_program->release();
}
