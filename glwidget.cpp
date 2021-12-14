#include "glwidget.h"

#include "lib/sphere.h"
#include "lib/room.h"
#include "lib/window.h"
#include "lib/resourceloader.h"
#include "lib/errorchecker.h"
#include "Settings.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "openglshape.h"
#include "iostream"
#include "gl/textures/Texture2D.h"
#include "gl/shaders/ShaderAttribLocations.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()),
      m_height(height()),
      m_phongProgram(0),
      m_glassProgram(0),
      m_textureProgram(0),
      m_terrainProgram(0),
      m_particleUpdateProgram(0),
      m_particleDrawProgram(0),
      m_sphere(nullptr),
      m_leftWall(nullptr),
      m_rightWall(nullptr),
      m_backWall(nullptr),
      m_ceiling(nullptr),
      m_floor(nullptr),
      m_windowSidePanels(nullptr),
      m_windowLowerPanel(nullptr),
      m_windowUpperPanel(nullptr),
      m_windowFrame(nullptr),
      m_quad(nullptr),
      m_particlesFBO1(nullptr),
      m_particlesFBO2(nullptr),
      m_firstPass(true),
      m_evenPass(true),
      m_numParticles(200),
      m_angleX(0.f),
      m_angleY(0.f),
      m_zoom(0.1f)
{}

GLWidget::~GLWidget()
{
    glDeleteVertexArrays(1, &m_particlesVAO);
}

void GLWidget::initializeOpenGLShape(std::unique_ptr<OpenGLShape> &shape, std::vector<GLfloat> vertices, int numVertices, bool hasTexture)
{
    shape->setVertexData(&vertices[0], vertices.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, numVertices);
    shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    shape->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, true);
    if (hasTexture) {
        shape->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    }
    shape->buildVAO();
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    resizeGL(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Creates the shader program that will be used for drawing.
    m_phongProgram = ResourceLoader::createShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");
    m_textureProgram = ResourceLoader::createShaderProgram(":/shaders/texture.vert", ":/shaders/texture.frag");
    m_terrainProgram = ResourceLoader::createShaderProgram(":/shaders/terrain.vert", ":/shaders/terrain.frag");
    m_particleUpdateProgram = ResourceLoader::createShaderProgram(":/shaders/quad.vert", ":/shaders/particles_update.frag");
    m_particleDrawProgram = ResourceLoader::createShaderProgram(":/shaders/particles_draw.vert", ":/shaders/particles_draw.frag");

    initializeRoom(); // Sets up the walls, floor, and ceiling
    //initializeTerrain(); // set up terrain
    initializeParticles(); // sets up particles

}

void GLWidget::initializeParticles() {
    std::vector<GLfloat> quadData = {-1, 1, 0, 0, 1, -1, -1, 0, 0, 0, 1, 1, 0, 1, 1, 1, -1, 0, 1, 0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    glGenVertexArrays(1, &m_particlesVAO);

    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
}

void GLWidget::initializeTexture(std::string texturePath, bool hasAlpha)
{
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_texture);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, numChannels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &numChannels, 0);
    if (data) {
        if (hasAlpha) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void GLWidget::initializeRoom() // Initialize the room's walls, floor, and ceiling
{
    // Initialize the room's walls, floor, and ceiling
    m_backWall = std::make_unique<OpenGLShape>();
    m_leftWall = std::make_unique<OpenGLShape>();
    m_rightWall = std::make_unique<OpenGLShape>();
    m_ceiling = std::make_unique<OpenGLShape>();
    m_floor = std::make_unique<OpenGLShape>();
    m_windowSidePanels = std::make_unique<OpenGLShape>();
    m_windowUpperPanel = std::make_unique<OpenGLShape>();
    m_windowLowerPanel = std::make_unique<OpenGLShape>();
    m_windowFrame = std::make_unique<OpenGLShape>();
    m_windowPane = std::make_unique<OpenGLShape>();
    m_sphere = std::make_unique<OpenGLShape>();

    initializeOpenGLShape(m_backWall, BACK_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_leftWall, LEFT_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_rightWall, RIGHT_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_ceiling, CEILING_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_floor, FLOOR_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_windowSidePanels, WINDOW_SIDE_PANELS_VERTEX_POSITIONS, NUM_WINDOW_SIDE_PANELS_VERTICES, true);
    initializeOpenGLShape(m_windowUpperPanel, WINDOW_UPPER_PANEL_VERTEX_POSITIONS, NUM_WINDOW_UPPER_PANEL_VERTICES, true);
    initializeOpenGLShape(m_windowLowerPanel, WINDOW_LOWER_PANEL_VERTEX_POSITIONS, NUM_WINDOW_LOWER_PANEL_VERTICES, true);
    initializeOpenGLShape(m_windowFrame, WINDOW_FRAME_VERTEX_POSITIONS, NUM_WINDOW_FRAME_VERTICES, true);
    initializeOpenGLShape(m_windowPane, WINDOW_FRAME_VERTEX_POSITIONS, NUM_WINDOW_FRAME_VERTICES, true);
    initializeOpenGLShape(m_sphere, SPHERE_VERTEX_POSITIONS, NUM_SPHERE_VERTICES, false);
}

void GLWidget::initializeTerrain() {

    std::vector<glm::vec3> terrainVertices = m_terrain.init();
    glPolygonMode(GL_FRONT_AND_BACK, m_terrain.isFilledIn() ? GL_FILL : GL_LINE);

    m_terrain.openGLShape = std::make_unique<OpenGLShape>();
    m_terrain.openGLShape->setVertexData(&terrainVertices[0][0], terrainVertices.size() * 3, VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 2 * terrainVertices.size());
    m_terrain.openGLShape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_terrain.openGLShape->setAttribute(ShaderAttrib::NORMAL, 3, sizeof(glm::vec3), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_terrain.openGLShape->buildVAO();
}

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 model(1.f);

//     Draw terrain.
    glUseProgram(m_terrainProgram);
//     Set uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_terrainProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_terrainProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_terrainProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    m_terrain.draw();

    glUseProgram(m_phongProgram);

    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));

    // Sets uniforms that are controlled by the UI.
    glUniform1f(glGetUniformLocation(m_phongProgram, "shininess"), 20.41f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "lightIntensity"), 5.f);
    glUniform4f(glGetUniformLocation(m_phongProgram, "lightColor"),
                1.f,
                1.f,
                1.f,
                1.f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attQuadratic"), 0.f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attLinear"), 0.81f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attConstant"), 2.16f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "ambientIntensity"), 0.28f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "diffuseIntensity"), 0.62f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "specularIntensity"), 0.59f);

    model = glm::translate(glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    rebuildMatrices();

    glUniform4f(glGetUniformLocation(m_phongProgram, "color"),
                0.f,
                0.f,
                0.f,
                1.f);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Switch to your own machine's absolute file path
    initializeTexture("/Users/annazhao/Anna/brown/graphics/cabin-fever/wood.jpg", false);

//    m_backWall->draw();
//    m_leftWall->draw();
//    m_rightWall->draw();
//    m_ceiling->draw();
//    m_floor->draw();

//    m_windowSidePanels->draw();
//    m_windowUpperPanel->draw();
//    m_windowLowerPanel->draw();

//    model = glm::translate(glm::vec3(-4.f, 2.f, -15.f));
//    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    glUniform4f(glGetUniformLocation(m_phongProgram, "color"),
//                0.2f,
//                0.90f,
//                0.98f,
//                1.f);
//    m_sphere->draw();

//    model = glm::translate(glm::vec3(4.f, 2.f, -15.f));
//    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    m_sphere->draw();

//    model = glm::translate(glm::vec3(4.f, -2.f, -15.f));
//    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    m_sphere->draw();

//    model = glm::translate(glm::vec3(-4.f, -2.f, -15.f));
//    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    m_sphere->draw();

//    glUseProgram(m_textureProgram);

//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//    glBindTexture(GL_TEXTURE_2D, m_texture);

//    initializeTexture("/Users/annazhao/Anna/brown/graphics/cabin-fever/pane.png", true);

//    model = glm::translate(glm::vec3(0.f, 0.f, -0.05f));
//    glUniformMatrix4fv(glGetUniformLocation(m_textureProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
//    glUniformMatrix4fv(glGetUniformLocation(m_textureProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
//    glUniformMatrix4fv(glGetUniformLocation(m_textureProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));

//    m_windowPane->draw();

//    glUseProgram(m_phongProgram);

//    glBindTexture(GL_TEXTURE_2D, m_texture);

//    initializeTexture("/Users/annazhao/Anna/brown/graphics/cabin-fever/windowframe.png", true);

//    model = glm::translate(glm::vec3(0.f, 0.f, 0.f));
//    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

//    glUniform4f(glGetUniformLocation(m_phongProgram, "color"),
//                0.08f,
//                0.05f,
//                0.05f,
//                1.f);

//    m_windowFrame->draw();

//    glDisable(GL_BLEND);

    drawParticles();
    update();

    glUseProgram(0);
}

void GLWidget::drawParticles() {
    auto prevFBO = m_evenPass ? m_particlesFBO1 : m_particlesFBO2;
    auto nextFBO = m_evenPass ? m_particlesFBO2 : m_particlesFBO1;
    float firstPass = m_firstPass ? 1.0f : 0.0f;

    // TODO [Task 14] Move the particles from prevFBO to nextFBO while updating them
    nextFBO->bind();
    glUseProgram(m_particleUpdateProgram);
    glActiveTexture(GL_TEXTURE0);
    prevFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    prevFBO->getColorAttachment(1).bind();

    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "firstPass"), firstPass);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "numParticles"), m_numParticles);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevPos"), 0);
    glUniform1i(glGetUniformLocation(m_particleUpdateProgram, "prevVel"), 1);
    glUniform1f(glGetUniformLocation(m_particleUpdateProgram, "gravity"), settings.snowRate);

    m_quad->draw();

    // TODO [Task 17] Draw the particles from nextFBO
    nextFBO->unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_particleDrawProgram);
    setParticleViewport();
    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "vel"), 1);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numParticles"), m_numParticles);
    glUniform1f(glGetUniformLocation(m_particleDrawProgram, "size"), settings.snowSize);
    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m_numParticles);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

    m_firstPass = false;
    m_evenPass = !m_evenPass;
}

void GLWidget::resizeGL(int w, int h) {
    m_width = w;
    m_height = h;
    glViewport(0, 0, w, h);
}

void GLWidget::setParticleViewport() {
    //glViewport(0, 0, m_width, m_height);
    int maxDim = std::max(m_width, m_height);
    int x = (m_width - maxDim) / 2.0f;
    int y = (m_height - maxDim) / 2.0f;
    glViewport(x, y, maxDim, maxDim);
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    m_prevMousePos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    m_angleX += 3 * (event->x() - m_prevMousePos.x()) / (float) width();
    m_angleY += 3 * (event->y() - m_prevMousePos.y()) / (float) height();
    m_prevMousePos = event->pos();
    rebuildMatrices();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
    m_zoom -= event->delta() / 100.f;
    rebuildMatrices();
}

void GLWidget::rebuildMatrices() {
    m_view = glm::translate(glm::vec3(0, 0, -m_zoom)) *
             glm::rotate(m_angleY, glm::vec3(1,0,0)) *
             glm::rotate(m_angleX, glm::vec3(0,1,0));

    m_projection = glm::perspective(0.8f, (float)width()/height(), 0.1f, 100.f);
    update();
}
