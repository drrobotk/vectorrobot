# vectorrobot

## Table of Contents  
[Overview](#overview)  
[Setup](#setup)  
[Creating a Project](#creating-a-project)  
[Creating a Header](#creating-a-header)  
[The vector3d Type](#the-vector3d-type)  
[Addition and Subtraction](#addition-and-subtraction)  
[Equality](#equality)

## Overview

We're going to write a very simple library for vector arithmetic. I'm also going to assume minimal C++ knowledge. Below I tend to use Visual Studio terminology, but none of the code in here (from me) is nonportable.

## Setup
Fork this repository and clone *your version* (not mine) somewhere on your machine. If you're using Visual Studio, follow these instructions for the GitHub extension: https://github.com/github/VisualStudio/blob/master/docs/using/cloning-a-repository-to-visual-studio.md If you're using the command-ine, just do a regular git clone. If you're using SourceTree or SmartGit or something else, please consult the documentation about how to clone.

## Creating a Project
Create a new console executable project. Give it the name you want your math library to have. Make sure the directories and files it generates are located inside of your forked repository so that I can follow your progress.

At the top of the generated .cpp file containing `main()`, do
```cpp
#include <cassert>
```

In `main()` on the line before the function returns add 
```cpp
assert(false);
```

Make sure the project configuration is set to Debug (in Release builds `assert()` will be disabled)

Build and Debug the app. What happens? Does it succeed (Exit code 0)? Copy the output from running it into a subdirectory called task1/output.txt and then push the changes to your fork.

Change the `assert(false)` to `assert(true)` and run it again. What changes?

## Creating a Header
Add a new header file to the project and call it vector3d.h
At the top of the header write 
```cpp
#pragma once
```

This line tells the C++ preprocessor to never include this file more than once. If you don't add this and you include it multiple times, you will get compile errors about multiply-defined symbols.

Let's wrap everything in your library in a namespace. If you called your math library mymathlib, for example, then a couple lines below the pragma write
```cpp
namespace mymathlib {
```

Your IDE should have automatically added a closing }, but if it didn't, add it now or else nothing will build

Inside of the namespace let's define a dummy constant (a value that cannot be modified at runtime) called XYZ:
```cpp
constexpr int XYZ = 42;
```

Now go back to your .cpp with main in it, and above the line that includes cassert, add:
```cpp
#include "vector3d.h"
```

Make sure you use "" instead of <> for the include, as we're including a local header and not a system header.

In main add another assert, but this time to make sure our include works:
```cpp
assert(XYZ == 41);
```

Try building. It failed, didn't it? That's because we forgot that XYZ is in the namespace "mymathlib." So let's fix that:
```cpp
assert(mymathlib::XYZ == 41);
```
Now build and debug. Did it crash? Good. Change 41 to 42. Why did I bother making it fail? This is how things are normally done when testing. You test the failure case first just to make sure it's failing when you want it to fail, and *then* test the opposite when everything should be assumed working.

When everything is ready, the output should be nothing but Exit code 0. That's fine. Copy it to a task2/output.txt like you did for Task 1 and push.

## The vector3d Type
Let's take a moment to decide how to proceed. The original goal was to have a simple vector arithmetic library. So probably a good next step would be defining the vector. There are lots of ways to do this, from the semantically stupid (C-arrays, std::array, std::vector) to the more correct but arguably inconvenient (std::tuple) to the typical (a struct) to the Bad Old Days typical (a class with a diamond inheritance pattern cribbed from a Gang of Four book and 8 vector factories). Let's stick with typical.

Open up vector3d.h and above our dummy XYZ constant let's define a struct called vector3d. We'll give it three components (x, y, and z--or i, j, and k if you prefer). We'll also mark it final for now since it seems unlikely we'll have to derive from it:
```cpp
struct vector3d final {
    float x = 0.f;
    float y = 0.f;
    float z = 0.f;
};
```

If the `0.f` is confusing, all we're doing is initializing `x`, `y`, and `z` with the default value of zero. The `.f` part simply makes it a zero of type `float`.

Let's do two more things and then this task is done. First, let's get rid of our dummy XYZ constant and define one for the unit vectors (sometimes called x-hat, j-hat, etc.). Remove `constexpr int XYZ = 42;` and replace it with `constexpr auto X_HAT = vector3d{1.f, 0.f, 0.f};` This might contain a lot of new concepts, so let's go through them. Whereas our old constant had type `int`, now all of a sudden it says `auto`. All this means is "let the compiler figure out what the type is." On the other side of the assignment, we're creating an instance of our `vector3d` struct and setting its x value to 1 and the rest to 0. 

Second, your project probably no longer builds because `XYZ` is gone. That's fine. Go back to the assert in main() that was using it and change it to `assert(mymathlib::X_HAT.x == 0.f);` This assertion will (hopefully) fail at runtime, because the unit vector for x should be 1. Verify the assertion fails, and then correct it so that it runs without failing.

Third (I lied; there's a third thing), add two additional constants Y_HAT and Z_HAT, add 2 more asserts to verify it fails when it should fail, and then fix the tests so that they pass.

We're done with this task. You know what to do at the end of a task by now and I won't continue mentioning it.

## Addition and Subtraction
Let's get down to business. We came here to arithmetize, so we'll start with addition. Open up vector3d.h and a few lines below your `vector3d` struct add the following function:
```cpp
       constexpr auto add(vector3d const v1, vector3d const v2) -> vector3d {
                return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
        }
```
As in previous tasks, this might contain some stuff you've never seen before (especially if you're taking one of those insufferable C++ courses that is stuck in 1998), so let's go through it slowly.

I've defined a function called `add` that takes two of our vector objects as arguments and returns a third vector containing the sum. I could tell you it's for performance reasons, but the `constexpr` is honestly only there because we haven't gotten around to adding additional .cpp files to a project yet and this is an easy way of defining it inline. 

The `auto` that follow constexpr says "I'll define the return type later." Feel free to replace it with the type `vector3d` if you prefer, but trust me, when this file contains 800 functions you'll be glad they all sort of line up with each other visually.

Next comes the name of the function, `add.` Call it `sum` if you like. If you're inclined to use `+`, we'll get to that later.

Following the function name are the arguments. The `const` following the type means "I don't intend to modify the argument so I'll add this const keyword to avoid any unfortunate accidents." Get used to using it whenever possible, because it will save you a lot of time and headaches in the future.

At the very end is a funky `-> vector3d`. This is the return type we promised at the start of the function when we wrote `auto.` If you are familiar with some higher forms of mathematics or functional programming languages, you might already have seen this syntax. In a perfect world, the `auto` wouldn't be necessary, but we do not live there, so write both.

Now, let's look at the actual body of the function. We're returning an unnamed object of type vector3d and initializing its x, y, and z members to the sums of the x, y, and z members of the two arguments, v1 and v2, respectively. Simple, right? No? Let me write it a little more explicitly then:
```cpp
vector3d my_temporary_vector;
my_temporary_vector.x = v1.x + v2.x;
my_temporary_vector.y = v1.y + v2.y;
my_temporary_vector.z = v1.z + v2.z;
return my_temporary_vector;
```
This is (effectively) equivalent to the original version above. Get used to (and play around with) both ways of writing functions.

Great, so hopefully that's working and we can switch back to our .cpp with `main()` and all of our asserts in it. We don't have an equality function yet so we'll have to do the assert to test `add()` in a couple steps. 

First, construct a test value somewhere in `main()`

```cpp
auto const testvec = mymathlib::add(mymathlib::X_HAT, mymathlib::Y_HAT);
```
Gross. If your namespace was longer than mine, double gross. Let's fix that. I'm not a huge fan of getting rid of namespaces completely with `using namespace`, but we can definitely make it smaller and less present. Somewhere outside of `main()` (just in case we add other functions we want to call later), but below the last `#include` add:

```cpp
namespace ml = mymathlib;
```

This defines an alias for the namespace called `ml` that looks *way* easier to read (in my opinion). Now we can go back and fix up the call to `add` and add some tests:

```cpp
auto const testvec = ml::add(ml::X_HAT, ml::Y_HAT);
assert(testvec.x == 0.f); // this should fail
assert(testvec.y == 75.f); // so should this
assert(testvec.z == 80.f); // and this
```
This test doesn't suitably cover the z component because we didn't add two vectors that even use z. I leave that as an exercise to the reader, as well another exercise to write a new function called `subtract` that subtracts the second vector from the first and returns a third vector containing the result. Don't forget to make your arguments `const` unless you intend to change them. And: Don't forget to write tests!

Bonus: if you want to see a cool side effect of defining our functions `constexpr`, try adding this somewhere in `main()`:

```cpp
static_assert(ml::add(ml::X_HAT, ml::X_HAT).x == 3.f);
```
When you try building it you should see an error similar to

```
main.cpp: In function ‘int main()’:
main.cpp:13:2: error: static assertion failed
  static_assert(ml::add(ml::X_HAT, ml::X_HAT).x == 3.f);
  ^~~~~~~~~~~~~
```
That's right. We're adding vectors at compile-time!

## Equality
One fairly obvious thing we haven't yet taken care of is equality. This is problematic with floats and doubles because of imprecision. Generally you decide on an epsilon and then check for equality by subtracting one value from the other and seeing if the absolute difference is within the epsilon. You can certainly go back and modify all of your asserts to do that, and at some point you probably should, but for now I'm trying to keep things relatively simple. With that said, let's actually define equality in our library now. What does it mean for two vectors to be equal (ignoring imprecision and epsilons)? It means the x components are equal, the y components are equal, and the z components are equal, no? OK, then let's write that:

```cpp
constexpr auto operator==(vector3d const v1, vector3d const v2) -> bool {
  return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
}
```

That weird `operator==` is a special syntax required by C++ for certain functions. Just go with it. Hopefully I don't need to explain the constexpr, auto, trailing return type, etc. by now and can focus on the implementation. I'm returning true if all the components are equal and false otherwise. Pretty straightforward. But only having an equality function is rather inconvenient. What if we want to test the opposite and see if two vectors *aren't* equal? Well, we *could* do it like this:

```cpp
constexpr auto operator!=(vector3d const v1, vector3d const v2) -> bool {
  return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z;
}
```

We compare each component pair separately and return false if any one of them is inequal. The reason we use a logical OR here (`||`) is that we want to short-circuit the evaluation. We don't care if all of them are inequal. In fact, that would be the wrong condition to test for. If *anything* isn't equal, the vectors aren't equal. Period.

We *could* implement `!=` like that and it would be perfectly fine. But I'll let you in on a secret: programmers are lazy. Since `==` is a cheap operation, why not get some more mileage out of it by reusing it in our `!=` implementation like so:

```cpp
constexpr auto operator!=(vector3d const v1, vector3d const v2) -> bool {
  return !(v1 == v2);
}
```

In other words, if v1 == v2, return false, else return true. Get used to seeing this pattern, because it is everywhere in C++. Not only because it saves time and space, but also because if I now change the implementation of `==`, I don't have to remember to rewrite `!=` as well.

Finally, let's add some tests. We can stick with compile-time tests for this one:

```cpp
static_assert(ml::X_HAT != ml::X_HAT);
static_assert(ml::Y_HAT != ml::Y_HAT);
static_assert(ml::Z_HAT != ml::Z_HAT);
static_assert(ml::X_HAT == ml::Y_HAT);
static_assert(ml::X_HAT == ml::Z_HAT);
static_assert(ml::Y_HAT == ml::Z_HAT);
```

Fix the expressions until they're correct (and it compiles), and you're done.
