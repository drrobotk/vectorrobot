// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "vector3d.h"

namespace ml = mymathlib;


int main()
{
    // Task 1
    assert(true);
    // Task 3
    assert(mymathlib::X_HAT.x == 1.f);
    assert(mymathlib::Y_HAT.x == 1.f);
    assert(mymathlib::Z_HAT.x == 1.f);

    // Task 4
    auto const testvec = ml::add(ml::X_HAT, ml::Y_HAT);
    auto const testvec2 = ml::add(testvec, ml::Y_HAT);
    auto const testvec3 = ml::subtract(testvec2, ml::X_HAT);
    auto const testvec4 = ml::subtract(testvec3, ml::Y_HAT);

    assert(testvec4.x == 0.f); 
    assert(testvec4.y == 0.f); 
    assert(testvec4.z == 1.f);

    // Task 5
    static_assert(ml::X_HAT == ml::X_HAT);
    static_assert(ml::Y_HAT == ml::Y_HAT);
    static_assert(ml::Z_HAT == ml::Z_HAT);
    static_assert(ml::X_HAT != ml::Y_HAT);
    static_assert(ml::X_HAT != ml::Z_HAT);
    static_assert(ml::Y_HAT != ml::Z_HAT);
}
