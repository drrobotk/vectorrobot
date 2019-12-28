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
}