#ifndef __Gua__canvas__
#define __Gua__canvas__

#include <cfloat>

#include "vector.h"
#include "color.h"
#include "vertex.h"
#include "matrix.h"
#include "mesh.h"


class Canvas {
    uint32_t *_pixels;
    float *_depthBuffer;

    int _bufferSize;

    float _width;
    float _height;

    void putPixel(int x, int y, float z, const Color &color) {
        int index = (int)(_width * y + x);

        if (_depthBuffer[index] < z) {
            return;
        }

        _depthBuffer[index] = z;
        _pixels[index] = color.uint32();
    }

    void drawScanline(const Vertex &v1, const Vertex &v2, int y, const Texture *texture);

    Vertex project(const Vertex &v, const Matrix &transform) const {
        Vector p = transform.transform(v.position);

        p.x = p.x * _width + _width / 2;
        p.y = -p.y * _height + _height / 2;

        return Vertex(p, v.normal, v.u, v.v, v.color);
    }

public:
    Canvas(uint32_t *pixels, float width, float height) {
        _pixels = pixels;
        _width = width;
        _height = height;

        _bufferSize = width * height;
        _depthBuffer = new float[_bufferSize];
    };

    virtual ~Canvas() {
        delete [] _depthBuffer;
    };

    void clear() {
        memset(_pixels, 0, sizeof(uint32_t) * _width * _height);
        std::fill(_depthBuffer, _depthBuffer + _bufferSize, FLT_MAX);
    }

    void drawPoint(const Vector &point, const Color &color) {
        if (point.x >= 0 && point.y >= 0 &&
            point.x < _width && point.y < _height) {
            putPixel(point.x, point.y, point.z, color);
        }
    }

    void drawLine(const Vertex &v1, const Vertex &v2);
    void drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Texture *texture);
    void drawMesh(const Mesh &mesh);

};

#endif
