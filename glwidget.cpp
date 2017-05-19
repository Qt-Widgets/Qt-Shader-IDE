#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent), speed(1), time(0)
{
    setMouseTracking(true);

    v_str += "uniform mat4 matrix;\n"
    "attribute vec4 posAttr;\n"
    "attribute vec4 colAttr;\n"
    "varying vec4 col;\n";

    f_str += "uniform float time;\n"
    "uniform sampler2D tex;\n"
    "varying vec4 col;\n"
    "uniform vec2 resolution;\n"
    "uniform vec2 mouse;\n";
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    prog = new QOpenGLShaderProgram(this);
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

    m_colors[0] = 1.0f;
    m_colors[1] = 1.0f;
    m_colors[2] = 1.0f;

    m_colors[3] = 1.0f;
    m_colors[4] = 1.0f;
    m_colors[5] = 1.0f;

    m_colors[6] = 1.0f;
    m_colors[7] = 1.0f;
    m_colors[8] = 1.0f;

    m_colors[9] = 1.0f;
    m_colors[10] = 1.0f;
    m_colors[11] = 1.0f;

    glClearColor(0, 0, 0, 1);
    v = new QOpenGLShader(QOpenGLShader::Vertex);
    f = new QOpenGLShader(QOpenGLShader::Fragment);
    if(!prog->link()) return;
    m_posAttr = prog->attributeLocation("posAttr");
    m_colAttr = prog->attributeLocation("colAttr");
    m_matrixUniform = prog->uniformLocation("matrix");
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT);

    if(!prog->shaders().size()) return;
    if(!prog->bind())
    {
        std::string error_out;
        if(!f->log().toStdString().empty())
            error_out += "In fragment shader:\n" + f->log().toStdString() + "\n";
        if(!v->log().toStdString().empty())
        error_out += "In vertex shader:\n" + v->log().toStdString() + "\n";
        if(prev_error != error_out && prev_error.size() != error_out.size())
        {
            prev_error = error_out;
            emit outputError(QString::fromStdString(error_out));
        }
        return;
    }
    prev_error.clear();
    emit noError();

    QMatrix4x4 matrix;
    time+=.02f * speed;

    prog->setAttributeArray( m_posAttr, m_vertices.data(), 3);
    prog->enableAttributeArray( m_posAttr );
    glDrawArrays( GL_QUADS, 0, 4);
    prog->disableAttributeArray( m_posAttr );

    prog->setAttributeArray( m_colAttr, m_colors.data(), 3);
    prog->enableAttributeArray( m_colAttr );
    glDrawArrays( GL_QUADS, 0, 4);
    prog->disableAttributeArray( m_colAttr );

    prog->setUniformValue("mouse", QPointF(mousePos.x()/(float)m_resolution[0],
                                           1.0f-mousePos.y()/(float)m_resolution[1]));
    prog->setUniformValue("time", time);

    prog->setUniformValueArray("resolution", m_resolution.data(), 1, 2);

    prog->setUniformValue(m_matrixUniform, matrix);

    prog->release();

}

void GLWidget::reset() { time = 0; }

void GLWidget::compile(QString v_src, QString f_src)
{
    QString v_strsrc(v_str);
    v_strsrc += v_src;
    prog->removeShader(v);
    v->compileSourceCode(v_strsrc);
    prog->addShader(v);

    QString f_strsrc(f_str);
    f_strsrc += f_src;
    prog->removeShader(f);
    f->compileSourceCode(f_strsrc);
    prog->addShader(f);
}

void GLWidget::resizeGL()
{
    m_resolution[0] = this->width();
    m_resolution[1] = this->height();
}

void GLWidget::stop() { prog->removeAllShaders(); }

void GLWidget::toggle()
{
    if(isHidden()) show();
    else close();
}

void GLWidget::speedGL(int s) { speed = s; }

GLWidget::~GLWidget()
{
    prog->removeAllShaders();
    delete prog;
    delete v;
    delete f;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    mousePos = event->pos();
}
