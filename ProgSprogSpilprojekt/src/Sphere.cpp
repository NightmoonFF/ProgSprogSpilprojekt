#include "Sphere.h"
#include <cmath>

Sphere::Sphere(float radius, unsigned int sectorCount, unsigned int stackCount) {

    printf("Creating Sphere\n");
    
    GenerateSphere(radius, sectorCount, stackCount);
    
    //vb.UpdateData(vertices.data(), vertices.size() * sizeof(float));
    //
    // va.Bind();
    // 
    //VertexBufferLayout layout;
    //layout.Push<float>(3);
    //va.AddBuffer(vb, layout);
    //ib.UpdateData(indices.data(), indices.size());
    //printf("Sphere created\n");
}

void Sphere::GenerateSphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
    const float PI = 3.14159265359f;
    float x, y, z, xy;
    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for (unsigned int i = 0; i <= stackCount; ++i) {
        stackAngle = PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectorCount; ++j) {
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }

    for (unsigned int i = 0; i < stackCount; ++i) {
        unsigned int k1 = i * (sectorCount + 1);
        unsigned int k2 = k1 + sectorCount + 1;

        for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }
            if (i != (stackCount - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}
