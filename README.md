# vectorrobot

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
* Inside of the namespace let's define a dummy constant called XYZ:
        `constexpr int XYZ = 42;`
* Now go back to your .cpp with main in it, and above the line that includes cassert, add:
        `#include "vector3d.h"`
  Make sure you use "" instead of <> for the include, as we're including a local header and not a system header
* In main add another assert, but this time to make sure our include works:
        `assert(XYZ == 41);`
* Try building. It failed, didn't it? That's because we forgot that XYZ is in the namespace "mymathlib." So let's $
        `assert(mymathlib::XYZ == 41);`
* Now build and debug. Did it crash? Good. Change 41 to 42. Why did I bother making it fail? This is how things
  are normally done when testing. You test the failure case first just to make sure it's failing when you want
  it to fail, and *then* test the opposite when everything should be assumed working.
* When everything is ready, the output should be nothing but Exit code 0. That's fine. Copy it to a task2/output.txt like you did for Task 1 and push.
