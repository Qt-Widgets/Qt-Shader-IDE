#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <QWidget>
#include <QMatrix4x4>
#include <GL/glew.h>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget*);
    ~GLWidget();

private:
    std::string vert, frag;

    GLuint current_shader;

    GLfloat time;

    std::vector<GLfloat> verts;
    GLuint vert_buffer;

    QMatrix4x4 *MVP;
    GLfloat rotY;

    void initializeGL();
    void paintGL();

public slots:
    void compileShader(std::string, std::string);
    void reset();
	void toggle();

signals:
    void shaderError(QString);
};

#endif // GLWIDGET_H
