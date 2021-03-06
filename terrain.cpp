#include "lib/terrain.h"
#include "Settings.h"
#include <math.h>
#include <iostream>
#include <glm.h>
#include "gl/shaders/ShaderAttribLocations.h"

Terrain::Terrain() : m_numRows(100), m_numCols(m_numRows), m_isFilledIn(true)
{
}


/**
 * Returns a pseudo-random value between -1.0 and 1.0 for the given row and
 * column.
 */
float Terrain::randValue(int row, int col, float a)
{
    return -a + 2.0 * a * glm::fract(sin(row * 127.1f + col * 311.7f) * 43758.5453123f);
}


/**
 * Returns the object-space position for the terrain vertex at the given row
 * and column.
 */
glm::vec3 Terrain::getPosition(int row, int col)
{

    glm::vec3 position;
    // in front of room: z(-9 to -30), x(-9 to 9)
    position.x = 60.f * row/m_numRows - 30; // centers around origin
    position.y = -3.01;
    position.z = 60.f * col/m_numCols - 30;

    if (position.x <= m_roomXRadius && position.x >= -m_roomXRadius) {
        if (position.z <= m_roomZRadius && position.z >= -m_roomZRadius) {
            return glm::vec3({position.x, -3.01, position.z}); // dont render terrain if is in room dimensions
        }
    }

     float a = 1 + settings.snowLevel;
     float f = 1 + settings.windiness;

     for (int i = 0; i < 3; i++) {
         int newRow = glm::floor(row / (20.0f / f));
         int newCol = glm::floor(col / (20.0f / f));

         float heightA = randValue(newRow, newCol, a);
         float heightB = randValue(newRow, newCol+1, a);
         float heightC = randValue(newRow+1, newCol, a);
         float heightD = randValue(newRow+1, newCol+1, a);

         float x = glm::fract(row / (20.0f / f));
         float z = glm::fract(col / (20.0f / f));

         float ab = glm::mix(heightA, heightB, z * z * (3 - 2 * z));
         float cd = glm::mix(heightC, heightD, z * z * (3 - 2 * z));
         float abcd = glm::mix(ab, cd, x * x * (3 - 2 * x));

         position.y += abcd;

         a *= 0.5;
         f *= 2;
     }

    return position;
}


/**
 * Returns the normal vector for the terrain vertex at the given row and
 * column.
 */
glm::vec3 Terrain::getNormal(int row, int col)
{
    glm::vec3 coords = getPosition(row, col);

    if (coords.x <= m_roomXRadius && coords.x >= -m_roomXRadius) {
        if (coords.z <= m_roomZRadius && coords.z >= -m_roomZRadius) {
            return glm::vec3({0.f, 1.f, 0.f}); // dont render terrain if is in room dimensions
        }
    }

    glm::vec3 neighbours[8];
    neighbours[0] = getPosition(row, col+1) - coords;
    neighbours[1] = getPosition(row+1, col+1) - coords;
    neighbours[2] = getPosition(row+1, col) - coords;
    neighbours[3] = getPosition(row+1, col-1) - coords;
    neighbours[4] = getPosition(row, col-1) - coords;
    neighbours[5] = getPosition(row-1, col-1) - coords;
    neighbours[6] = getPosition(row-1, col) - coords;
    neighbours[7] = getPosition(row-1, col+1) - coords;

    float sum_x = 0;
    float sum_y = 0;
    float sum_z = 0;
    for (int i = 0; i < 8; i++) {
        glm::vec3 adj_vect;
        adj_vect = (i == 8) ? adj_vect = neighbours[0] : adj_vect = neighbours[i+1];
        glm::vec3 norm_vect = glm::normalize(glm::cross(neighbours[i], adj_vect));
        sum_x += norm_vect[0];
        sum_y += norm_vect[1];
        sum_z += norm_vect[2];
    }

    return glm::vec3(sum_x/8.0, sum_y/8.0, sum_z/8.0);
}

bool Terrain::isFilledIn() {
    return m_isFilledIn;
}

/**
 * Initializes the terrain by storing positions and normals in a vertex buffer.
 */
std::vector<glm::vec3> Terrain::init() {
    // Initializes a grid of vertices using triangle strips.
    int numVertices = (m_numRows - 1) * (2 * m_numCols + 2);
    std::vector<glm::vec3> data(2 * numVertices);
    int index = 0;
    for (int row = 0; row < m_numRows - 1; row++) {
        for (int col = m_numCols - 1; col >= 0; col--) {
            data[index++] = getPosition(row, col);
            data[index++] = getNormal  (row, col);
            data[index++] = getPosition(row + 1, col);
            data[index++] = getNormal  (row + 1, col);
        }
        data[index++] = getPosition(row + 1, 0);
        data[index++] = getNormal  (row + 1, 0);
        data[index++] = getPosition(row + 1, m_numCols - 1);
        data[index++] = getNormal  (row + 1, m_numCols - 1);
    }

    return data;
}


/**
 * Draws the terrain.
 */
void Terrain::draw()
{
    openGLShape->draw();
}

void Terrain::settingsChanged() {
    this->init();
}
