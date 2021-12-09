#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <memory>

#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>
#include "lib/sphere.h"

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

class OpenGLShape;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void initializeRoom();
    void initializeQuad(std::unique_ptr<OpenGLShape> &quad, std::vector<GLfloat> vertices);
private:
    /** ID for the shader program. */
    GLuint m_program;

    std::unique_ptr<OpenGLShape> m_sphere;
    std::unique_ptr<OpenGLShape> m_rect;
    std::unique_ptr<OpenGLShape> m_leftWall;
    std::unique_ptr<OpenGLShape> m_rightWall;
    std::unique_ptr<OpenGLShape> m_frontWall;
    std::unique_ptr<OpenGLShape> m_backWall;
    std::unique_ptr<OpenGLShape> m_ceiling;
    std::unique_ptr<OpenGLShape> m_floor;
    std::unique_ptr<OpenGLShape> m_windowLeftPanel;
    std::unique_ptr<OpenGLShape> m_windowRightPanel;
    std::unique_ptr<OpenGLShape> m_windowTopPanel;
    std::unique_ptr<OpenGLShape> m_windowBottomPanel;

    void rebuildMatrices();
    glm::mat4 m_view, m_projection;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_zoom;
    QPoint m_prevMousePos;
};

#endif // GLWIDGET_H
