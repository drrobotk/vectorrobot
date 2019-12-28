// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cassert>
#include "vector3d.h"

namespace ml = mymathlib;
using namespace std;

int main()
{
    assert(true);
    auto const testvec = ml::add(ml::X_HAT, ml::Y_HAT);
    auto const testvec2 = ml::add(testvec, ml::Z_HAT);
    auto const testvec3 = ml::subtract(testvec2, ml::X_HAT);
    auto const testvec4 = ml::subtract(testvec3, ml::Y_HAT);


    assert(testvec4.x == 0.f);
    assert(testvec4.y == 0.f); 
    assert(testvec4.z == 1.f); 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
