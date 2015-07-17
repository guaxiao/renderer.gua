#include "color.h"


Color::Color(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

uint32_t
Color::uint32() const {
    uint32_t R = (uint32_t)(r * 255.0f);
    uint32_t G = (uint32_t)(g * 255.0f);
    uint32_t B = (uint32_t)(b * 255.0f);
    uint32_t A = (uint32_t)(a * 255.0f);
    
    // mac
#ifdef __APPLE__
    uint32_t value = (B << 24) | (G << 16) | (R << 8) | A;
    // windows with mingw
#elif __MINGW32__
    uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
#elif __linux
    uint32_t value = (A << 24) | (R << 16) | (G << 8) | B;
#endif
    return value;
}
