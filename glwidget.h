#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <memory>

#include "GL/glew.h"
#include <QGLWidget>
#include <QTimer>
#include "lib/terrain.h"
#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "gl/datatype/FBO.h"

class OpenGLShape;

using namespace CS123::GL;

class GLWidget : public QGLWidget {
    Q_OBJECT

public:
    GLWidget(QGLFormat format, QWidget *parent = 0);
    ~GLWidget();
    void snowballPressed();

protected:
    struct TextureInfo {
        std::string name;
        bool hasAlpha;
    };

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void initializeRoom();
    void initializeTerrain();
    void initializeScene();
    void initializeParticles();
    void initializeOpenGLShape(std::unique_ptr<OpenGLShape> &quad, std::vector<GLfloat> vertices, int numVertices, bool hasTexture);
    void initializeTextures();
    void loadTexture(TextureInfo texInfo);
    void drawRoom();
    void drawTerrain();
    void drawScene();
    void drawWindow();
    void drawParticles();
    void setParticleViewport();
private:
    int m_width;
    int m_height;

    /** ID for the shader programs. */
    GLuint m_phongProgram;
    GLuint m_glassProgram;
    GLuint m_textureProgram;
    GLuint m_terrainProgram;
    GLuint m_particleUpdateProgram;
    GLuint m_particleDrawProgram;

    std::unique_ptr<OpenGLShape> m_moon;
    std::unique_ptr<OpenGLShape> m_snowball;
    std::unique_ptr<OpenGLShape> m_leftWall;
    std::unique_ptr<OpenGLShape> m_rightWall;
    std::unique_ptr<OpenGLShape> m_backWall;
    std::unique_ptr<OpenGLShape> m_ceiling;
    std::unique_ptr<OpenGLShape> m_floor;
    std::unique_ptr<OpenGLShape> m_windowSidePanels;
    std::unique_ptr<OpenGLShape> m_windowLowerPanel;
    std::unique_ptr<OpenGLShape> m_windowUpperPanel;
    std::unique_ptr<OpenGLShape> m_windowFrame;
    std::unique_ptr<OpenGLShape> m_windowPane;
    std::unique_ptr<OpenGLShape> m_frontLeftPainting;
    std::unique_ptr<OpenGLShape> m_frontRightPainting;
    std::unique_ptr<OpenGLShape> m_rightPainting;
    std::unique_ptr<OpenGLShape> m_leftPainting;
    std::unique_ptr<OpenGLShape> m_backLeftPainting;
    std::unique_ptr<OpenGLShape> m_backRightPainting;
    std::unique_ptr<OpenGLShape> m_door;

    glm::vec3 m_snowballPos;
    glm::vec3 m_snowballVelocity;
    bool m_snowballPressed;

    // Update this array whenever a new texture is added
    GLuint m_textures[10];

    Terrain m_terrain;

    std::unique_ptr<OpenGLShape> m_quad;

    GLuint m_particlesVAO;
    std::shared_ptr<FBO> m_particlesFBO1;
    std::shared_ptr<FBO> m_particlesFBO2;
    bool m_firstPass;
    bool m_evenPass;
    int m_numParticles;

    void rebuildMatrices();
    glm::mat4 m_model, m_view, m_projection;

    /** For mouse interaction. */
    float m_angleX, m_angleY, m_zoom;
    QPoint m_prevMousePos;
};

#endif // GLWIDGET_H
