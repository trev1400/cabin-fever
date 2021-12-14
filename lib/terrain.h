#ifndef TERRAIN_H
#define TERRAIN_H

#include "glm/glm.hpp"            // glm::vec*, mat*, and basic glm functions
#include "glm/gtx/transform.hpp"  // glm::translate, scale, rotate
#include "glm/gtc/type_ptr.hpp"   // glm::value_ptr
#include <vector>

#include "openglshape.h"

class Terrain {
public:
    Terrain();

    std::vector<glm::vec3> init();
    void draw();

    std::unique_ptr<OpenGLShape> openGLShape;
    bool isFilledIn();

private:
    float randValue(int row, int col);
    glm::vec3 getPosition(int row, int col);
    glm::vec3 getNormal(int row, int col);
    const float m_numRows, m_numCols;
    const int m_roomXRadius = 9;
    const int m_roomZRadius = 9; // room width, length
    const bool m_isFilledIn;
};

#endif // TERRAIN_H
