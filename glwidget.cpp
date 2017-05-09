#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), scale(1), speed(1) {}

void GLWidget::initializeGL()
{
    m_resolution.resize(2);
    m_resolution[0] = this->width();
    m_resolution[1] = this->height();

    m_vertices.resize( 12 );

    m_vertices[0] = -2.0f;
    m_vertices[1] = -2.0f;
    m_vertices[2] = 0.0f;

    m_vertices[3] = -2.0f;
    m_vertices[4] = 2.0f;
    m_vertices[5] = 0.0f;

    m_vertices[6] = 2.0f;
    m_vertices[7] = 2.0f;
    m_vertices[8] = 0.0f;

    m_vertices[9] = 2.0f;
    m_vertices[10] = -2.0f;
    m_vertices[11] = 0.0f;

    m_colors.resize( 12 );

    m_colors[0] = 0.0f;
    m_colors[1] = 0.0f;
    m_colors[2] = 0.0f;

    m_colors[3] = 0.0f;
    m_colors[4] = 0.0f;
    m_colors[5] = 0.0f;

    m_colors[6] = 0.0f;
    m_colors[7] = 0.0f;
    m_colors[8] = 0.0f;

    m_colors[9] = 0.0f;
    m_colors[10] = 0.0f;
    m_colors[11] = 0.0f;

    glClearColor(0, 0, 0, 1);
    QOpenGLShader v(QOpenGLShader::Vertex);
    v.compileSourceCode("attribute highp vec4 posAttr;\n"
                        "uniform mediump mat4 matrix;\n"
                        "attribute lowp vec4 colAttr;\n"
                        "varying lowp vec4 col;\n"
                        "void main() {\n"
                        "   col = colAttr;\n"
                        "   gl_Position = matrix * posAttr;\n"
                        "}\n");
    f = new QOpenGLShader(QOpenGLShader::Fragment);
    prog.addShader(&v);
    if(!prog.link()) return;
    m_posAttr = prog.attributeLocation("posAttr");
    m_colAttr = prog.attributeLocation("colAttr");
    m_matrixUniform = prog.uniformLocation("matrix");
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    prog.bind();

    QMatrix4x4 matrix;

    time+=.02f * speed;
    prog.setAttributeArray( m_posAttr, m_vertices.data(), 3);
    prog.setAttributeArray( m_colAttr, m_colors.data(), 3);
    prog.enableAttributeArray( m_posAttr );
    prog.enableAttributeArray( m_colAttr );

    if(QString(f->sourceCode()).toStdString().find("uniform float time")!=std::string::npos)
        prog.setUniformValue("time", time);

    if(QString(f->sourceCode()).toStdString().find("uniform vec2 resolution")!=std::string::npos)
        prog.setUniformValueArray("resolution", m_resolution.data(), 1, 2);
    glDrawArrays( GL_QUADS, 0, 4);
    prog.disableAttributeArray( m_posAttr );
    prog.disableAttributeArray( m_colAttr );

    prog.setUniformValue(m_matrixUniform, matrix);

    prog.release();

}

void GLWidget::reset() { time = 0; }

void GLWidget::compile(QString src)
{
    prog.removeShader(f);
    f->compileSourceCode(src);
    prog.addShader(f);
}

void GLWidget::resizeGL()
{
    m_resolution[0] = this->width();
    m_resolution[1] = this->height();
}

void GLWidget::stop() { prog.removeShader(f); }

void GLWidget::toggle()
{
    if(isHidden()) show();
    else close();
}

void GLWidget::speedGL(int s) { speed = s; }
