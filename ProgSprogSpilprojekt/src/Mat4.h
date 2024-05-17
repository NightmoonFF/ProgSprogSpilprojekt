#pragma once

#include "Vec3.h"
#include <cmath>
#include <array>

class Mat4 {
public:
    std::array<std::array<float, 4>, 4> data;

    Mat4() {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                data[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    static Mat4 translate(const Vec3& vec) {
        Mat4 result;
        result.data[3][0] = vec.x;
        result.data[3][1] = vec.y;
        result.data[3][2] = vec.z;
        return result;
    }

    static Mat4 perspective(float fov, float aspect, float near, float far) {
        Mat4 result;
        float tanHalfFov = std::tan(fov / 2.0f);
        result.data[0][0] = 1.0f / (aspect * tanHalfFov);
        result.data[1][1] = 1.0f / tanHalfFov;
        result.data[2][2] = -(far + near) / (far - near);
        result.data[2][3] = -1.0f;
        result.data[3][2] = -(2.0f * far * near) / (far - near);
        result.data[3][3] = 0.0f;
        return result;
    }

    static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        Vec3 f = (center - eye).normalize();
        Vec3 u = up.normalize();
        Vec3 s = Vec3::cross(f, u).normalize();
        u = Vec3::cross(s, f);

        Mat4 result;
        result.data[0][0] = s.x;
        result.data[1][0] = s.y;
        result.data[2][0] = s.z;
        result.data[0][1] = u.x;
        result.data[1][1] = u.y;
        result.data[2][1] = u.z;
        result.data[0][2] = -f.x;
        result.data[1][2] = -f.y;
        result.data[2][2] = -f.z;
        result.data[3][0] = -Vec3::dot(s, eye);
        result.data[3][1] = -Vec3::dot(u, eye);
        result.data[3][2] = Vec3::dot(f, eye);
        return result;
    }

    Mat4 operator*(const Mat4& other) const {
        Mat4 result;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                result.data[i][j] = data[i][0] * other.data[0][j] +
                data[i][1] * other.data[1][j] +
                data[i][2] * other.data[2][j] +
                data[i][3] * other.data[3][j];
        return result;
    }

    static Mat4 rotateY(float angle) {
        float cosA = std::cos(angle);
        float sinA = std::sin(angle);

        Mat4 rotationMatrix;
        rotationMatrix.data[0][0] = cosA;
        rotationMatrix.data[0][2] = sinA;
        rotationMatrix.data[1][1] = 1.0f;
        rotationMatrix.data[2][0] = -sinA;
        rotationMatrix.data[2][2] = cosA;
        rotationMatrix.data[3][3] = 1.0f;

        return rotationMatrix;
    }
};