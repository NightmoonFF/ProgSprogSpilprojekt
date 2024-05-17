#pragma once

#include <vector>
#include <glm/glm.hpp>

class Sphere {
public:
    Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);

    const std::vector<float>& getVertices() const { return vertices; }
    const std::vector<unsigned int>& getIndices() const { return indices; }

private:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    float radius;
    unsigned int sectorCount;
    unsigned int stackCount;
};
