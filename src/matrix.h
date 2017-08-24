#ifndef __Gua__matrix__
#define __Gua__matrix__


#include <cmath>
#include <cstdio>

#include "vector.h"
#include "guamath.h"


class Matrix {
public:
    float p[16];

    Matrix() {
        for(int i = 0; i < 16; i++) {
            p[i] = 0;
        }
    };

    Matrix(float values[]) {
        memcpy(p, values, sizeof(float)*16);
    };

    bool operator==(const Matrix &m) const {
        bool equal = true;
        for (int i = 0; i < 16; i++) {
            equal = equal && floatEqual(p[i], m.p[i]);
        }
        return equal;
    };

    static Matrix identity() {
        float values[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
        };
        return Matrix(values);
    };

    static Matrix lookAtLH(const Vector &eye, const Vector &target, const Vector &up) {
        Vector axisZ = (target - eye).normalize();
        Vector axisX = up.cross(axisZ).normalize();
        Vector axisY = axisZ.cross(axisX).normalize();

        float eyeX = -axisX.dot(eye);
        float eyeY = -axisY.dot(eye);
        float eyeZ = -axisZ.dot(eye);

        float values[16] = {
            axisX.x, axisY.x, axisZ.x, 0,
            axisX.y, axisY.y, axisZ.y, 0,
            axisX.z, axisY.z, axisZ.z, 0,
            eyeX,    eyeY,    eyeZ,    1,
        };

        return Matrix(values);
    };

    static Matrix perspectiveFovLH(float fieldOfView, float aspect, float znear, float zfar) {
        float height = 1 / tan(fieldOfView / 2);
        float width = height / aspect;
        float values[16] = {
            width,  0,      0,                                  0,
            0,      height, 0,                                  0,
            0,      0,      zfar / (zfar - znear),              1,
            0,      0,      (znear * zfar) / (znear - zfar),    0,
        };
        return Matrix(values);
    };

    static Matrix rotationX(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        float values[16] = {
            1, 0,  0, 0,
            0, c,  s, 0,
            0, -s, c, 0,
            0, 0,  0, 1,
        };
        return Matrix(values);
    }

    static Matrix rotationY(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        float values[16] = {
            c, 0, -s, 0,
            0, 1, 0,  0,
            s, 0, c,  0,
            0, 0, 0,  1,
        };
        return Matrix(values);
    }

    static Matrix rotationZ(float angle) {
        float s = sinf(angle);
        float c = cosf(angle);
        float values[16] = {
            c,  s, 0, 0,
            -s, c, 0, 0,
            0,  0, 1, 0,
            0,  0, 0, 1,
        };
        return Matrix(values);
    }

    static Matrix rotation(const Vector &r) {
        Matrix x = Matrix::rotationX(r.x);
        Matrix y = Matrix::rotationY(r.y);
        Matrix z = Matrix::rotationZ(r.z);
        return z * x * y;
    }

    static Matrix translation(const Vector &t) {
        float values[16] = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            t.x, t.y, t.z, 1,
        };
        return Matrix(values);
    }

    static Matrix scale(const Vector &s) {
        float values[16] = {
            s.x, 0,   0,    0,
            0,   s.y, 0,    0,
            0,   0,   s.z,  0,
            0,   0,   0,    1,
        };
        return Matrix(values);
    }

    Vector transform(const Vector &v) const {
        float x = v.x * p[0*4 + 0] + v.y * p[1*4 + 0] + v.z * p[2*4 + 0] + p[3*4 + 0];
        float y = v.x * p[0*4 + 1] + v.y * p[1*4 + 1] + v.z * p[2*4 + 1] + p[3*4 + 1];
        float z = v.x * p[0*4 + 2] + v.y * p[1*4 + 2] + v.z * p[2*4 + 2] + p[3*4 + 2];
        float w = v.x * p[0*4 + 3] + v.y * p[1*4 + 3] + v.z * p[2*4 + 3] + p[3*4 + 3];
        return Vector(x/w, y/w, z/w);
    }

    Matrix operator*(const Matrix &matrix) const {
        const Matrix &m = matrix;

        float values[16];
        for(int index = 0; index < 16; index++) {
            int i = index / 4;
            int j = index % 4;
            values[index] = p[i*4] * m.p[j] + p[i*4 + 1] * m.p[1*4 + j] + p[i*4 + 2] * m.p[2*4 + j] + p[i*4 + 3] * m.p[3*4 + j];
        }
        return Matrix(values);
    };
};

#endif
