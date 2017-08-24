#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

#include "canvas.h"

void
Canvas::drawLine(const Vertex &v1, const Vertex &v2) {
    int x1 = (int)v1.position.x;
    int y1 = (int)v1.position.y;
    int x2 = (int)v2.position.x;
    int y2 = (int)v2.position.y;

    // delta x and delta y
    int dx = x2 - x1;
    int dy = y2 - y1;

    if(abs(dx) > abs(dy)) {
        int sign = x2 - x1 > 0 ? 1 : -1;
        float ratio = 0;
        if (dx != 0) {
            ratio = (float)dy / dx;
        }

        for (int x = x1; x != x2; x += sign) {
            int y = y1 + (x - x1) * ratio;
            Color c = v1.color + ((v2.color - v1.color) * ((float)(x - x1)/(x2 - x1)));
            drawPoint(Vector(x, y), c);
        }
    } else {
        int sign = y2 - y1 > 0 ? 1 : -1;
        float ratio = 0;
        if (dy != 0) {
            ratio = (float)dx / dy;
        }

        for (int y = y1; y != y2; y += sign) {
            int x = x1 + (y - y1) * ratio;
            Color c = v1.color + ((v2.color - v1.color) * ((float)(y - y1)/(y2 - y1)));
            drawPoint(Vector(x, y), c);
        }
    }
}

void
Canvas::drawScanline(const Vertex &v1, const Vertex &v2, int y, const Texture *texture) {
    int x1 = v1.position.x;
    int x2 = v2.position.x;

    // int sign = x2 > x1 ? 1 : -1
    int sign = ((((unsigned)(x1 - x2)) >> 30) & 0x2) - 1;
    float factor = 0;

    for (int x = x1, i = 0; i < (x2 - x1) * sign + 1; i++, x += sign) {
        if (x2 != x1) {
            factor = (float)(x - x1) / (x2 - x1);
        }
        auto v = v1.interpolate(v2, factor);
        auto color = texture->sample(v.u, v.v);

        drawPoint(v.position, color);
    }
}

void
Canvas::drawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, const Texture *texture) {
    // sort a b c by y, top to bottom
    const Vertex *a = &v1;
    const Vertex *b = &v2;
    const Vertex *c = &v3;
    if (a->position.y > b->position.y) {
        std::swap(a, b);
    }
    if (b->position.y > c->position.y) {
        std::swap(b, c);
    }
    if (a->position.y > b->position.y) {
        std::swap(a, b);
    }

    float middleFactor = (float)(b->position.y - a->position.y) / (c->position.y - a->position.y);
    Vertex middle = a->interpolate(*c, middleFactor);

    int startY = a->position.y;
    int endY = b->position.y;
    for (int y = startY; y <= endY; ++y) {
        float factor = 0;
        if (endY != startY) {
            factor = (float)(y - startY) / (endY - startY);
        }
        Vertex va = a->interpolate(*b, factor);
        Vertex vb = a->interpolate(middle, factor);
        drawScanline(va, vb, y, texture);
    }
    startY = b->position.y;
    endY = c->position.y;
    for (int y = startY; y <= endY; ++y) {
        float factor = 0;
        if (endY != startY) {
            factor = (float)(y - startY) / (endY - startY);
        }
        Vertex va = b->interpolate(*c, factor);
        Vertex vb = middle.interpolate(*c, factor);
        drawScanline(va, vb, y, texture);
    }
}

void
Canvas::drawMesh(const Mesh &mesh) {
    static const auto cameraPosition = Vector(0, 0, -10);
    static const auto cameraTarget = Vector(0, 0, 0);
    static const auto cameraUp = Vector(0, 1, 0);

    static auto view = Matrix::lookAtLH(cameraPosition, cameraTarget, cameraUp);
    static auto projection = Matrix::perspectiveFovLH(radiansFromDegrees(45), _width / _height, 0.1, 1);
    auto rotation = Matrix::rotation(mesh.rotation);
    auto translation = Matrix::translation(mesh.position);
    auto scale = Matrix::scale(mesh.scale);

    auto world = scale * rotation * translation;
    auto transform = world * view * projection;

    for(unsigned int i = 0; i < mesh.indices.size(); i += 3) {
        const Vertex &a = mesh.vertices[mesh.indices[i]];
        const Vertex &b = mesh.vertices[mesh.indices[i+1]];
        const Vertex &c = mesh.vertices[mesh.indices[i+2]];

        auto v1 = project(a, transform);
        auto v2 = project(b, transform);
        auto v3 = project(c, transform);

        drawTriangle(v1, v2, v3, mesh.texture);
    }
}
