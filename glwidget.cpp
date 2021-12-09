#include "glwidget.h"

#include "lib/sphere.h"
#include "lib/rect.h"
#include "lib/room.h"
#include "lib/window.h"
#include "lib/resourceloader.h"
#include "lib/errorchecker.h"
#include "Settings.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include "openglshape.h"
#include "iostream"
#include "gl/shaders/ShaderAttribLocations.h"

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_program(0),
      m_angleX(0.f),
      m_angleY(0.f),
      m_zoom(0.5f)
{}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeOpenGLShape(std::unique_ptr<OpenGLShape> &shape, std::vector<GLfloat> vertices, int numVertices)
{
    shape->setVertexData(&vertices[0], vertices.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, numVertices);
    shape->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    shape->buildVAO();
}

void GLWidget::initializeRoom()
{
    // Initialize the room's walls, floor, and ceiling
    std::vector<GLfloat> frontVertices = FRONT_WALL_VERTEX_POSITIONS;
    m_frontWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_frontWall, frontVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> backVertices = BACK_WALL_VERTEX_POSITIONS;
    m_backWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_backWall, backVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> leftVertices = LEFT_WALL_VERTEX_POSITIONS;
    m_leftWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_leftWall, leftVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> rightVertices = RIGHT_WALL_VERTEX_POSITIONS;
    m_rightWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_rightWall, rightVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> ceilingVertices = CEILING_VERTEX_POSITIONS;
    m_ceiling = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_ceiling, ceilingVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> floorVertices = FLOOR_VERTEX_POSITIONS;
    m_floor = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_floor, floorVertices, NUM_QUAD_VERTICES);

    std::vector<GLfloat> windowVertices = WINDOW_VERTEX_POSITIONS;
    m_window = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_window, windowVertices, NUM_WINDOW_VERTICES);
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    resizeGL(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Creates the shader program that will be used for drawing.
    m_program = ResourceLoader::createShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");

    // Sets up the walls, floor, and ceiling
    initializeRoom();
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model(1.f);

    glUseProgram(m_program);

    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_program, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "view"), 1, GL_FALSE, glm::value_ptr(m_view));

    // Sets uniforms that are controlled by the UI.
    glUniform1f(glGetUniformLocation(m_program, "shininess"), 20.41f);
    glUniform1f(glGetUniformLocation(m_program, "lightIntensity"), 5.f);
    glUniform3f(glGetUniformLocation(m_program, "lightColor"),
                1.f,
                1.f,
                1.f);
    glUniform1f(glGetUniformLocation(m_program, "attQuadratic"), 0.f);
    glUniform1f(glGetUniformLocation(m_program, "attLinear"), 0.81f);
    glUniform1f(glGetUniformLocation(m_program, "attConstant"), 2.16f);
    glUniform1f(glGetUniformLocation(m_program, "ambientIntensity"), 0.28f);
    glUniform1f(glGetUniformLocation(m_program, "diffuseIntensity"), 0.62f);
    glUniform1f(glGetUniformLocation(m_program, "specularIntensity"), 0.59f);

    model = glm::translate(glm::vec3(0.f, 0.f, 0.f));
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    rebuildMatrices();

    glUniform3f(glGetUniformLocation(m_program, "color"),
                1.f,
                0.39f,
                0.9f);
    m_backWall->draw();
    // Draws the window on the front wall. Window is made up of 4 quads
    m_window->draw();

    glUniform3f(glGetUniformLocation(m_program, "color"),
                0.f,
                0.67f,
                1.f);
    m_leftWall->draw();
    m_rightWall->draw();

    glUniform3f(glGetUniformLocation(m_program, "color"),
                0.67f,
                1.f,
                0.f);
    m_ceiling->draw();
    m_floor->draw();


    glUseProgram(0);
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
