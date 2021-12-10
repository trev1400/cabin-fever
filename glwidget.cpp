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
#include "gl/textures/Texture2D.h"

#define PI 3.14159265f

GLWidget::GLWidget(QGLFormat format, QWidget *parent)
    : QGLWidget(format, parent),
      m_width(width()), m_height(height()),
      m_program(0),
      m_phongProgram(0), m_textureProgram(0), m_horizontalBlurProgram(0), m_verticalBlurProgram(0),
      m_quad(nullptr), m_sphere(nullptr),
      m_blurFBO1(nullptr), m_blurFBO2(nullptr),
      m_particlesFBO1(nullptr), m_particlesFBO2(nullptr),
      m_firstPass(true), m_evenPass(true), m_numParticles(100),
      m_angleX(0.f),
      m_angleY(0.f),
      m_zoom(0.1f)
{}

GLWidget::~GLWidget()
{
    glDeleteVertexArrays(1, &m_particlesVAO);
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
    m_phongProgram = ResourceLoader::createShaderProgram(
                ":/shaders/phong.vert", ":/shaders/phong.frag");
    m_textureProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/texture.frag");
    m_horizontalBlurProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/horizontalBlur.frag");
    m_verticalBlurProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/verticalBlur.frag");
    m_particleUpdateProgram = ResourceLoader::createShaderProgram(
                ":/shaders/quad.vert", ":/shaders/particles_update.frag");
    m_particleDrawProgram = ResourceLoader::createShaderProgram(
                ":/shaders/particles_draw.vert", ":/shaders/particles_draw.frag");
    // initialise a rect
    std::vector<GLfloat> rectData = RECT_VERTEX_POSITIONS;
    m_rect = std::make_unique<OpenGLShape>();
    m_rect->setVertexData(&rectData[0], rectData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_RECT_VERTICES);
    m_rect->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
//    m_rect->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, true);
    m_rect->buildVAO();

    // initialize a sphere
    std::vector<GLfloat> sphereData = SPHERE_VERTEX_POSITIONS;
    m_sphere = std::make_unique<OpenGLShape>();
    m_sphere->setVertexData(&sphereData[0], sphereData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLES, NUM_SPHERE_VERTICES);
    m_sphere->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->setAttribute(ShaderAttrib::NORMAL, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_sphere->buildVAO();

    std::vector<GLfloat> quadData = {-1, 1, 0, 0, 1, -1, -1, 0, 0, 0, 1, 1, 0, 1, 1, 1, -1, 0, 1, 0};
    m_quad = std::make_unique<OpenGLShape>();
    m_quad->setVertexData(&quadData[0], quadData.size(), VBO::GEOMETRY_LAYOUT::LAYOUT_TRIANGLE_STRIP, 4);
    m_quad->setAttribute(ShaderAttrib::POSITION, 3, 0, VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->setAttribute(ShaderAttrib::TEXCOORD0, 2, 3*sizeof(GLfloat), VBOAttribMarker::DATA_TYPE::FLOAT, false);
    m_quad->buildVAO();

    glGenVertexArrays(1, &m_particlesVAO);
    // TODO [Task 13] Create m_particlesFBO1 and 2 with std::make_shared
    m_particlesFBO1 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);
    m_particlesFBO2 = std::make_shared<FBO>(2, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, m_numParticles, 1, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE, TextureParameters::FILTER_METHOD::NEAREST, GL_FLOAT);

    // Print the max FBO dimension.
    GLint maxRenderBufferSize;
    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &maxRenderBufferSize);

    // Sets up the walls, floor, and ceiling
    initializeRoom();

}

void GLWidget::paintGL() {
    //auto rectFBO = std::make_shared<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, 1, 1);

    //rectFBO->bind();
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
    std::cout << "draw" << std::endl;
//    drawParticles();
//    update();
}

void GLWidget::drawParticles() {

    auto prevFBO = m_evenPass ? m_particlesFBO1 : m_particlesFBO2;
    auto nextFBO = m_evenPass ? m_particlesFBO2 : m_particlesFBO1;
    float firstPass = m_firstPass ? 1.0f : 0.0f;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    m_quad->draw();

    // TODO [Task 17] Draw the particles from nextFBO
    nextFBO->unbind();
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_particleDrawProgram);
    setParticleViewport();
    glActiveTexture(GL_TEXTURE0);
    nextFBO->getColorAttachment(0).bind();
    glActiveTexture(GL_TEXTURE1);
    nextFBO->getColorAttachment(1).bind();
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "pos"), 0);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "vel"), 1);
    glUniform1i(glGetUniformLocation(m_particleDrawProgram, "numParticles"), m_numParticles);
    glBindVertexArray(m_particlesVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3 * m_numParticles);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

    m_firstPass = false;
    m_evenPass = !m_evenPass;
}

void GLWidget::resizeGL(int w, int h) {
//    glViewport(0, 0, w, h);
    m_width = w;
    m_height = h;

    // TODO: [Task 5] Initialize FBOs here, with dimensions m_width and m_height.
    m_blurFBO1 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::DEPTH_ONLY, w, h);
    //       [Task 12] Pass in TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE as the last parameter
    m_blurFBO2 = std::make_unique<FBO>(1, FBO::DEPTH_STENCIL_ATTACHMENT::NONE, w, h, TextureParameters::WRAP_METHOD::CLAMP_TO_EDGE);
    //rebuildMatrices();
}

void GLWidget::setParticleViewport() {
    glViewport(0, 0, m_width, m_height);
//    int maxDim = std::max(m_width, m_height);
//    int x = (m_width - maxDim) / 2.0f;
//    int y = (m_height - maxDim) / 2.0f;
//    glViewport(x, y, maxDim, maxDim);
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
