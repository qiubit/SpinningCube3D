#include <QString>

#include "cubewindow.h"

static GLfloat const triangleVertices[] = {
    -0.75f, 0.75f, -1.0f, 1.0f,
    -0.75f, -0.75f, -1.0f, 1.0f,
    0.75f, -0.75f, -1.0f, 1.0f
};

static const char* vertexShaderSrc =
        "#version 330\n"
        "layout(location = 0) in vec4 position;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";

static const char* fragmentShaderSrc =
        "#version 330\n"
        "out vec4 outputColor;\n"
        "void main()\n"
        "{\n"
        "   outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n";

CubeWindow::CubeWindow(UpdateBehavior updateBehavior,
                       QWindow *parent) :
    QOpenGLWindow(updateBehavior, parent)
{
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
}

void CubeWindow::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    m_program->enableAttributeArray(m_posAtr);
    m_program->setAttributeArray(m_posAtr, triangleVertices, 4);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_program->disableAttributeArray(m_posAtr);

    m_program->release();
}
