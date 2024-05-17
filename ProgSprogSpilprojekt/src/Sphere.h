#pragma once

#include <vector>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class Sphere {
public:
    Sphere(float radius, unsigned int sectorCount, unsigned int stackCount);
    //VertexArray va;
    //VertexBuffer vb;
    //IndexBuffer ib;
    //const VertexArray& GetVertexArray() const { return va; }
    //const IndexBuffer& GetIndexBuffer() const { return ib; }
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

private:
    void GenerateSphere(float radius, unsigned int sectorCount, unsigned int stackCount);


};
