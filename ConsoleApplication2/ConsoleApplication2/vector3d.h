#pragma once
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
}