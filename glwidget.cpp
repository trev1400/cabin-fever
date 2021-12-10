#include "glwidget.h"

#include "lib/sphere.h"
#include "lib/rect.h"
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

void GLWidget::initializeRoom()
{
    // Initialize the room's walls, floor, and ceiling
    std::vector<GLfloat> frontVertices = FRONT_WALL_VERTEX_POSITIONS;
    m_frontWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_frontWall, frontVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> backVertices = BACK_WALL_VERTEX_POSITIONS;
    m_backWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_backWall, backVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> leftVertices = LEFT_WALL_VERTEX_POSITIONS;
    m_leftWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_leftWall, leftVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> rightVertices = RIGHT_WALL_VERTEX_POSITIONS;
    m_rightWall = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_rightWall, rightVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> ceilingVertices = CEILING_VERTEX_POSITIONS;
    m_ceiling = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_ceiling, ceilingVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> floorVertices = FLOOR_VERTEX_POSITIONS;
    m_floor = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_floor, floorVertices, NUM_QUAD_VERTICES, true);

    std::vector<GLfloat> windowVertices = WINDOW_VERTEX_POSITIONS;
    m_window = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_window, windowVertices, NUM_WINDOW_VERTICES, true);

    std::vector<GLfloat> windowPaneVertices = WINDOW_PANE_VERTEX_POSITIONS;
    m_windowPane = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_windowPane, windowPaneVertices, NUM_WINDOW_PANE_VERTICES, false);

    std::vector<GLfloat> sphereVertices = SPHERE_VERTEX_POSITIONS;
    m_sphere = std::make_unique<OpenGLShape>();
    initializeOpenGLShape(m_sphere, sphereVertices, NUM_SPHERE_VERTICES, false);
}

void GLWidget::initializeGL() {
    ResourceLoader::initializeGlew();
    resizeGL(width(), height());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Set the color to set the screen when the color buffer is cleared.
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Set up the phong shader program
    m_phongProgram = ResourceLoader::createShaderProgram(":/shaders/phong.vert", ":/shaders/phong.frag");
    // Set up glass shader program
    m_glassProgram = ResourceLoader::createShaderProgram(":/shaders/glass.vert", ":/shaders/glass.frag");


    // Sets up the walls, floor, and ceiling
    initializeRoom();
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
    glUniform3f(glGetUniformLocation(m_phongProgram, "lightColor"),
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

    glUniform3f(glGetUniformLocation(m_phongProgram, "color"),
                0.25f,
                0.2f,
                0.2f);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    initializeTexture("container.jpeg");

    m_backWall->draw();
    m_leftWall->draw();
    m_rightWall->draw();
    m_ceiling->draw();

    initializeTexture("flooring.jpg");

    m_floor->draw();
    //     Draws the window on the front wall. Window is made up of 4 quads
    m_window->draw();


    model = glm::translate(glm::vec3(0.f, 0.f, -15.f));
    glUniformMatrix4fv(glGetUniformLocation(m_phongProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3f(glGetUniformLocation(m_phongProgram, "color"),
                0.49f,
                0.63f,
                0.85f);
    m_sphere->draw();

    glUseProgram(0);

    glUseProgram(m_glassProgram);

    // Sets projection and view matrix uniforms.
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(m_glassProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform1f(glGetUniformLocation(m_glassProgram, "r0"), 0.5f);
    glUniform1f(glGetUniformLocation(m_glassProgram, "eta1D"), 0.77f);
    glUniform3f(glGetUniformLocation(m_glassProgram, "eta"),
                0.8f,
                0.8f,
                0.8f);
    rebuildMatrices();
    m_windowPane->draw();

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
