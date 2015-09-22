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

const float ROTATION_TIME = 3.0f;

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
        "uniform mat4 transformationMatrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = transformationMatrix * position;\n"
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
    m_colorAtr = m_program->attributeLocation("color");
    m_transformationMatrixUniform = m_program->uniformLocation("transformationMatrix");

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

    m_currentYRotationAngle =
            fmod(m_currentYRotationAngle + rotationScale * 360.0f, 360.0f);

    QMatrix4x4 matrix;
    matrix.frustum(-0.75f, 0.75f, -0.75f, 0.75f, 1.0f, 3.0f);
    matrix.translate(0, 0, -2);
    matrix.rotate(m_currentYRotationAngle, 1.0f, 1.0f, 0.0f);
    matrix.translate(0, 0, 2);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepthf(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program->bind();
    m_program->setUniformValue(m_transformationMatrixUniform, matrix);

    m_program->enableAttributeArray(m_posAtr);
    m_program->setAttributeArray(m_posAtr, cubeVertices, 4);
    m_program->enableAttributeArray(m_colorAtr);
    m_program->setAttributeArray(m_colorAtr, colorData, 4);

    glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

    m_program->disableAttributeArray(m_posAtr);
    m_program->disableAttributeArray(m_colorAtr);

    m_program->release();
}
