#include "glwidget.h"

#include "lib/sphere.h"
#include "lib/rect.h"
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
      m_sphere(nullptr),
      m_angleX(-0.5f),
      m_angleY(0.5f),
      m_zoom(4.f)
{}

GLWidget::~GLWidget()
{
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

    // Initialize sphere with radius 0.5 centered at origin.
//    std::vector<GLfloat> sphereData = SPHERE_VERTEX_POSITIONS;
//    m_sphere = std::make_unique<OpenGLShape>();
//    m_sphere->setVertexData(&sphereData[0], sphereData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_SPHERE_VERTICES);
//    m_sphere->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
//    m_sphere->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, true);
//    m_sphere->buildVAO();

    // initialise a rect
    std::vector<GLfloat> rectData = RECT_VERTEX_POSITIONS;
    m_rect = std::make_unique<OpenGLShape>();
    m_rect->setVertexData(&rectData[0], rectData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_RECT_VERTICES);
    m_rect->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_rect->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, true);
    m_rect->buildVAO();
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

    // Draws a sphere at the origin.
    model = glm::mat4(1.f);
    glUniformMatrix4fv(glGetUniformLocation(m_program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(m_program, "color"),
                1.f,
                0.39f,
                0.9f);
    rebuildMatrices();
//    m_sphere->draw();
    m_rect->draw();

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
