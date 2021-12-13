#include "glwidget.h"

#include "lib/sphere.h"
#include "lib/room.h"
#include "lib/window.h"
#include "lib/windowpane.h"
#include "lib/resourceloader.h"
#include "lib/errorchecker.h"
#include "Settings.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "openglshape.h"
#include "iostream"
#include "gl/shaders/ShaderAttribLocations.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_phongProgram(0),
      m_glassProgram(0),
      m_textureProgram(0),
      m_terrainProgram(0),
      m_sphere(nullptr),
      m_leftWall(nullptr),
      m_rightWall(nullptr),
      m_frontWall(nullptr),
      m_backWall(nullptr),
      m_ceiling(nullptr),
      m_floor(nullptr),
      m_window(nullptr),
      m_windowPane(nullptr),
      m_angleX(0.f),
      m_angleY(0.f),
      m_zoom(0.1f)
{}

GLWidget::~GLWidget()
{
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
//    m_terrainProgram = ResourceLoader::createShaderProgram(":/shaders/terrain.vert", ":/shaders/terrain.frag");

    initializeRoom(); // Sets up the walls, floor, and ceiling
    initializeTerrain(); // set up terrain
}

void GLWidget::initializeTexture(std::string texturePath)
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void GLWidget::initializeRoom() // Initialize the room's walls, floor, and ceiling
{
    m_frontWall = std::make_unique<OpenGLShape>();
    m_backWall = std::make_unique<OpenGLShape>();
    m_leftWall = std::make_unique<OpenGLShape>();
    m_rightWall = std::make_unique<OpenGLShape>();
    m_ceiling = std::make_unique<OpenGLShape>();
    m_floor = std::make_unique<OpenGLShape>();
    m_window = std::make_unique<OpenGLShape>();
    m_windowPane = std::make_unique<OpenGLShape>();
    m_sphere = std::make_unique<OpenGLShape>();

    initializeOpenGLShape(m_frontWall, FRONT_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_backWall, BACK_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_leftWall, LEFT_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_rightWall, RIGHT_WALL_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_ceiling, CEILING_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_floor, FLOOR_VERTEX_POSITIONS, NUM_QUAD_VERTICES, true);
    initializeOpenGLShape(m_window, WINDOW_VERTEX_POSITIONS, NUM_WINDOW_VERTICES, true);
    initializeOpenGLShape(m_windowPane, WINDOW_PANE_VERTEX_POSITIONS, NUM_WINDOW_PANE_VERTICES, true);
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

    glUseProgram(m_phongProgram);

    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));

    // Sets uniforms that are controlled by the UI.
    glUniform1f(glGetUniformLocation(m_phongProgram, "shininess"), 20.41f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "lightIntensity"), 5.f);
    glUniform3f(glGetUniformLocation(m_phongProgram, "lightColor"), 1.f, 1.f, 1.f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attQuadratic"), 0.f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attLinear"), 0.81f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "attConstant"), 2.16f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "ambientIntensity"), 0.28f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "diffuseIntensity"), 0.62f);
    glUniform1f(glGetUniformLocation(m_phongProgram, "specularIntensity"), 0.59f);

    model = glm::translate(glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    rebuildMatrices();

    glUniform3f(glGetUniformLocation(m_phongProgram, "color"), 0.25f, 0.2f, 0.2f);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    initializeTexture("container.jpeg");

    m_backWall->draw();
    m_leftWall->draw();
    m_rightWall->draw();
    m_ceiling->draw();

    initializeTexture("flooring.jpg");

    m_floor->draw();
    m_window->draw(); // Draws the window on the front wall. Window is made up of 4 quads

    model = glm::translate(glm::vec3(0.f, 0.f, -15.f));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(m_phongProgram, "color"), 0.49f, 0.63f, 0.85f);
    m_sphere->draw();

    glUseProgram(m_glassProgram);

    model = glm::translate(glm::vec3(0.f, 0.f, 0.f));

    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1f(glGetUniformLocation(m_glassProgram, "r0"), 0.5f);
    glUniform1f(glGetUniformLocation(m_glassProgram, "eta1D"), 0.77f);
    glUniform3f(glGetUniformLocation(m_glassProgram, "eta"), 0.8f, 0.8f, 0.8f);
    rebuildMatrices();
    m_windowPane->draw();

     Draw terrain.
    glUseProgram(m_phongProgram);
     Set uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniform3f(glGetUniformLocation(m_phongProgram, "color"), 0.90f, 0.90f, 0.90f);
    m_terrain.draw();

    glUseProgram(0); // unbind
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
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
