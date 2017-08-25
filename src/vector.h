#ifndef __Gua__vector__
#define __Gua__vector__


#include "guamath.h"


class Vector {
public:
    float x;
    float y;
    float z;

    Vector(float x=0.0f, float y=0.0f, float z=0.0f) {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    float length() const {
        return sqrtf(x*x + y*y + z*z);
    }

    Vector normalize() const {
        float factor = 0.0f;
        float sqLen = x*x + y*y + z*z;
        if (sqLen > 0.0f) {
            factor = 1.0f/sqrtf(sqLen);
        }
        return Vector(x*factor, y*factor, z*factor);
    }

    float dot(const Vector &v) const {
        return x*v.x + y*v.y + z*v.z;
    }

    Vector cross(const Vector &v) const  {
        float X = y * v.z - z * v.y;
        float Y = z * v.x - x * v.z;
        float Z = x * v.y - y * v.x;
        return Vector(X, Y, Z);
    }

    Vector interpolate(const Vector &v, float factor) const {
        return *this + (v - *this) * factor;
    }

    Vector operator+(const Vector &v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    };

    Vector operator-(const Vector &v) const {
        return Vector(x - v.x, y - v.y, z - v.z);
    };

    Vector operator*(float factor) const {
        return Vector(x * factor, y * factor, z * factor);
    };

    bool operator==(const Vector &v) const {
        return floatEqual(x, v.x) && floatEqual(y, v.y) && floatEqual(z, v.z);
    };
};

#endif
