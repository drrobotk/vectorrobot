#include <cmath>

#pragma once

constexpr float pi = 3.141592f;

namespace mymathlib {
    struct vector3d final {
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
    };

 

    constexpr auto X_HAT = vector3d{ 1.f, 0.f, 0.f };
    constexpr auto Y_HAT = vector3d{ 0.f, 1.f, 0.f };
    constexpr auto Z_HAT = vector3d{ 0.f, 0.f, 1.f };

    constexpr auto add(vector3d const v1, vector3d const v2) -> vector3d {
        return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    }

    constexpr auto subtract(vector3d const w1, vector3d const w2) -> vector3d {
        return { w1.x - w2.x, w1.y - w2.y, w1.z - w2.z };
    }

    constexpr auto operator==(vector3d const v1, vector3d const v2) -> bool {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    constexpr auto operator!=(vector3d const v1, vector3d const v2) -> bool {
        return !(v1 == v2);
    }

    constexpr auto operator+(vector3d const v1, vector3d const v2) -> vector3d {
        return add(v1, v2);
    }

    constexpr auto operator-(vector3d const v1, vector3d const v2) -> vector3d {
        return subtract(v1, v2);
    }

    constexpr auto operator+=(vector3d& v1, vector3d const v2) -> vector3d& {
        return v1 = add(v1, v2);
    }

    constexpr auto operator-=(vector3d& v1, vector3d const v2) -> vector3d& {
        return v1 = subtract(v1, v2);
    }

    constexpr auto dot(vector3d const v1, vector3d const v2) -> float {
        return { v1.x * v2.x + v1.y * v2.y + v1.z * v2.z };
    }

    constexpr auto cross(vector3d const v1, vector3d const v2) -> vector3d {
        return { v1.y * v2.z - v1.z * v2.y, v1.x * v2.z - v1.z * v2.x, v1.x * v2.y - v1.y * v2.x };
    }

    inline auto magnitude(vector3d const v) -> float {
        return std::sqrt(dot(v, v));
    }

    constexpr auto scale(vector3d const v, float a, float b, float c) -> vector3d {
        return { a * v.x, b * v.y, c * v.z };
    }

    constexpr auto scale(vector3d const v, float a) -> vector3d {
        return scale(v, a, a, a);
    }

    auto rotatex(vector3d v, float alpha)-> vector3d {
        return { v.x, v.y * cos(alpha) - v.z * sin(alpha), v.y * sin(alpha) + v.z * cos(alpha) };
    }

    auto rotatey(vector3d v, float alpha)-> vector3d {
        return { v.x * cos(alpha) + v.z * sin(alpha), v.y, -v.x * sin(alpha) + v.z * cos(alpha) };
    }

    auto rotatez(vector3d v, float alpha)-> vector3d {
        return { v.x * cos(alpha) - v.y * sin(alpha), v.x * sin(alpha) + v.y * cos(alpha), v.z};
    }

    auto rotate(vector3d v, float alpha, float beta, float gamma)-> vector3d {
        return rotatez(rotatey(rotatex(v, alpha), beta), gamma);
    }

    auto angle(vector3d const v1, vector3d const v2) -> float {
        return { acos(dot(v1,v2)/(magnitude(v1)*magnitude(v2))) };
    }

    auto angled(vector3d const v1, vector3d const v2) -> float {
        return { angle(v1,v2)*180/pi };
    }
}
