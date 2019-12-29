// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "vector3d.h"

namespace ml = mymathlib;
using namespace std;

int main()
{
    // Task 1

    assert(true);

    // Task 3
    assert(mymathlib::X_HAT.x == 1.f);
    assert(mymathlib::Y_HAT.y == 1.f);
    assert(mymathlib::Z_HAT.z == 1.f);

    // Task 4
    auto const testvec = ml::add(ml::X_HAT, ml::Y_HAT);
    auto const testvec2 = ml::add(testvec, ml::Z_HAT);
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

    // Task 6
        // Testing +
    auto testvec5 = ml::X_HAT;
    auto testvec6 = ml::Y_HAT;
    auto testvec7 = testvec5 + testvec6;
    assert(testvec7.x == 1.f);
    assert(testvec7.y == 1.f);
    assert(testvec7.z == 0.f);

        // Testing -
    auto testvec8 = testvec5 - testvec6;
    assert(testvec8.x == 1.f);
    assert(testvec8.y == -1.f);
    assert(testvec8.z == 0.f);

        // Testing +=
    testvec5 += testvec6;
    assert(testvec5 == (ml::X_HAT + ml::Y_HAT));
    (testvec5 += testvec6) += testvec6;
    assert(testvec5.x == 1.f);
    assert(testvec5.y == 3.f);
    assert(testvec5.z == 0.f);


        // Testing +-
    auto testvec9 = ml::X_HAT;
    auto testvec10 = ml::Y_HAT;
    testvec9 -= testvec10;
    assert(testvec9 == (ml::X_HAT - ml::Y_HAT));
    (testvec9 -= testvec10) -= testvec10;
    assert(testvec9.x == 1.f);
    assert(testvec9.y == -3.f);
    assert(testvec9.z == 0.f);

    cout << angled(ml::X_HAT, ml::Y_HAT);
    
    
}
