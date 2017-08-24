#ifndef __Gua__texture__
#define __Gua__texture__

#include <cstring>

#include "color.h"
#include "guaimage.h"

class Texture {
    uint32_t *_pixels;
    int _width;
    int _height;

public:
    Texture(const char *path) {
        GuaImage image = GuaImage(path);
        int w = image.width;
        int h = image.height;
        uint32_t *pixels = new uint32_t[w * h];
        memcpy(pixels, image.pixels, sizeof(uint32_t) * w * h);

        _pixels = pixels;
        _width = w;
        _height = h;
    }

    virtual ~Texture() {
        delete [] _pixels;
    };

    Color sample(float u, float v) const {
        int tu = abs((int)(u * (_width - 1)));
        int tv = abs((int)(v * (_height - 1)));

        int index = tu + tv * _width;

        return Color(_pixels[index]);
    }
};

#endif
