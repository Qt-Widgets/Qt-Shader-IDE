#ifndef GLSLSYNTAX_H
#define GLSLSYNTAX_H

#include <QWidget>
#include <QSyntaxHighlighter>

class GLSLSyntax : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit GLSLSyntax(QWidget *parent = 0);
};

#endif // GLSLSYNTAX_H
