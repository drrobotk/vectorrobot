// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "vector3d.h"

namespace ml = mymathlib;


int main()
{
    assert(true);
    static_assert(ml::X_HAT == ml::X_HAT);
    static_assert(ml::Y_HAT == ml::Y_HAT);
    static_assert(ml::Z_HAT == ml::Z_HAT);
    static_assert(ml::X_HAT != ml::Y_HAT);
    static_assert(ml::X_HAT != ml::Z_HAT);
    static_assert(ml::Y_HAT != ml::Z_HAT);
}
