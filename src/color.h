#ifndef __Gua__color__
#define __Gua__color__


#include <cstdlib>
#include <cstdint>


class Color {

public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    Color(int red = 255, int green = 255, int blue = 255, int alpha = 255)
    : r(red), g(green), b(blue), a(alpha)
    {}

    Color(uint32_t rgba) {
        r = ((rgba & 0xff000000) >> 24);
        g = ((rgba & 0x00ff0000) >> 16);
        b = ((rgba & 0x0000ff00) >> 8);
        a = (rgba & 0x000000ff);
    }

    static Color randomColor() {
        int r = (rand() % 256);
        int g = (rand() % 256);
        int b = (rand() % 256);

        return Color(r, g, b, 255);
    };

    uint32_t uint32() const {
        uint32_t R = r;
        uint32_t G = g;
        uint32_t B = b;
        uint32_t A = a;

    #ifdef __APPLE__
        uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
        // visual studio
    #elif _WIN32
        uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
    #else
        uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
    #endif
        return value;
    }

    Color operator+(const Color &color) const {
        return Color(r + color.r, g + color.g, b + color.b, a + color.a);
    };

    Color operator-(const Color &color) const {
        return Color(r - color.r, g - color.g, b - color.b, a - color.a);
    };

    Color operator*(float factor) const {
        return Color(r * factor, g * factor, b * factor, a * factor);
    };

    Color interpolate(const Color &c, float factor) const {
        return *this + (c - *this) * factor;
    };
};

#endif
