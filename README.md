# vectorrobot

## Overview

* We're going to write a very simple library for vector arithmetic. I'm also going to assume minimal C++ knowledge. Below I tend to use Visual Studio terminology, but none of the code in here (from me) is nonportable.

## Task 0
* Fork this repository and clone *your version* (not mine) somewhere on your machine. If you're using Visual Studio, follow these instructions for the GitHub extension: https://github.com/github/VisualStudio/blob/master/docs/using/cloning-a-repository-to-visual-studio.md If you're using the command-ine, just do a regular git clone. If you're using SourceTree or SmartGit or something else, please consult the documentation about how to clone.

## Task 1
* Create a new console executable project. Give it the name you want your math library to have. Make sure the directories and files it generates are located inside of your forked repository so that I can follow your progress.
* At the top of the generated .cpp file containing `main()`, do
        `#include <cassert>`
* In `main()` on the line before the function returns add
        `assert(false);`
* Make sure the project configuration is set to Debug (in Release builds `assert()` will be disabled)
* Build and Debug the app. What happens? Does it succeed (Exit code 0)? Copy the output from running it into a subdirectory called task1/output.txt and then push the changes to your fork.
* Change the `assert(false)` to `assert(true)` and run it again. What changes?

## Task 2
* Add a new header file to the project and call it vector3d.h
* At the top of the header write
        `#pragma once`
  This line tells the C++ preprocessor to never include this file more than once. If you don't add this
  and you include it multiple times, you will get compile errors about multiply-defined symbols
* Let's wrap everything in your library in a namespace. If you called your math library mymathlib, for example,
  then a couple lines below the pragma write
        `namespace mymathlib {`
  Your IDE should have automatically added a closing }, but if it didn't, add it now or else nothing will build
* Inside of the namespace let's define a dummy constant (a value that cannot be modified at runtime) called XYZ:
        `constexpr int XYZ = 42;`
* Now go back to your .cpp with main in it, and above the line that includes cassert, add:
        `#include "vector3d.h"`
  Make sure you use "" instead of <> for the include, as we're including a local header and not a system header
* In main add another assert, but this time to make sure our include works:
        `assert(XYZ == 41);`
* Try building. It failed, didn't it? That's because we forgot that XYZ is in the namespace "mymathlib." So let's fix that:
        `assert(mymathlib::XYZ == 41);`
* Now build and debug. Did it crash? Good. Change 41 to 42. Why did I bother making it fail? This is how things
  are normally done when testing. You test the failure case first just to make sure it's failing when you want
  it to fail, and *then* test the opposite when everything should be assumed working.
* When everything is ready, the output should be nothing but Exit code 0. That's fine. Copy it to a task2/output.txt like you did for Task 1 and push.

## Task 3
* Let's take a moment to decide how to proceed. The original goal was to have a simple vector arithmetic library. So probably a good next step would be defining the vector. There are lots of ways to do this, from the semantically stupid (C-arrays, std::array, std::vector) to the more correct but arguably inconvenient (std::tuple) to the typical (a struct) to the Bad Old Days typical (a class with a diamond inheritance pattern cribbed from a Gang of Four book and 8 vector factories). Let's stick with typical.
* Open up vector3d.h and above our dummy XYZ constant let's define a struct called vector3d. We'll give it three components (x, y, and z--or i, j, and k if you prefer). We'll also mark it final for now since it seems unlikely we'll have to derive from it:
`struct vector3d final {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};`
  If the `0.f` is confusing, all we're doing is initializing `x`, `y`, and `z` with the default value of zero. The `.f` part simply makes it a zero of type `float`.
* Let's do two more things and then this task is done. First, let's get rid of our dummy XYZ constant and define one for the unit vectors (sometimes called x-hat, j-hat, etc.). Remove `constexpr int XYZ = 42;` and replace it with `constexpr auto X_HAT = vector3d{1.f, 0.f, 0.f};` This might contain a lot of new concepts, so let's go through them. Whereas our old constant had type `int`, now all of a sudden it says `auto.` All this means is "let the compiler figure out what the type is." On the other side of the assignment, we're creating an instance of our `vector3d` struct and setting its x value to 1 and the rest to 0. 
* Second, your project probably no longer builds because `XYZ` is gone. That's fine. Go back to the assert in main() that was using it and change it to `assert(mymathlib::X_HAT.x == 0.f);` This assertion will (hopefully) fail at runtime, because the unit vector for x should be 1. Verify the assertion fails, and then correct it so that it runs without failing.
* Third, add two additional constants Y_HAT and Z_HAT, add 2 more asserts to verify it fails when it should fail, and then fix the tests so that they pass.
* We're done with this task. You know what to do at the end of a task by now and I won't continue mentioning it.
