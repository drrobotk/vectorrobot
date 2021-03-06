# vectorrobot

## Table of Contents  
[Overview](#overview)  
[Setup](#setup)  
[Creating a Project](#creating-a-project)  
[Creating a Header](#creating-a-header)  
[The vector3d Type](#the-vector3d-type)  
[Addition and Subtraction](#addition-and-subtraction)  
[Equality](#equality)
[Addition and Subtraction Revisited](#addition-and-subtraction-revisited)  
[Products and Such](#products-and-such)  
[Output](#output)  
[Commands](#commands)  
[A Command Processor](#a-command-processor)  

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

Output dir: task1/

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

Output dir: task2/

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

Output dir: task3/

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

Output dir: task4/

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

Output dir: task5/

## Addition and Subtraction Revisited

Remember when I said some people prefer using `+` for addition and `-` for subtraction? Well, now that we've dipped our toes in the waters of operator overloading, we can do that:

```cpp
constexpr auto operator+(vector3d const v1, vector3d const v2) -> vector3d {
  return add(v1, v2);
}
```
By now I trust you can implement operator- by yourself (you already wrote a `subtract()` function, right?).

But what if we want to add a second vector to the first and overwrite the value that was in the first? Sort of like

```cpp
auto x = 5;
auto y = 10;
x += y; // now x contains 15
```
You're ruining the beautiful immutability of our math library, but OK, OK, I yield. You've discovered operator overloading and now you want to find an excuse to overload all of them. Let's get this out of your system now so you'll get bored doing it:

```cpp
constexpr auto operator+=(vector3d& v1, vector3d const v2) -> vector3d& {
  v1.x += v2.x;
  v1.y += v2.y;
  v1.z += v2.z;
  return v1;
}
```

or even just:

```cpp
constexpr auto operator+=(vector3d& v1, vector3d const v2) -> vector3d& {
  return v1 = add(v1,v2);
}
```

Whichever version you prefer, there are two key differences to other functions we've written till now:

* First, we take the first argument by reference (`&`) so that we can modify it. If we don't do this, then whoever calls the function will end up with the same value as before because they passed in a copy.
* Second, now we have to return a reference as well, because C++ expects this to be possible:

```cpp
(v1 += v2) += v3;
```
If we *don't* return a reference from += then v3 will be added to a copy of v1 += v2 rather than v1 itself. Confused yet? Good. Stop overloading operators willy-nilly.

Add some tests to `main()` for + and += (and - and -= if you wrote them) and we're finished. Here's a sample of some tests you could do for `+=`:

```cpp
auto testvec2 = ml::X_HAT;
auto testvec3 = ml::Y_HAT;
testvec2 += testvec3;
assert(testvec2 == (ml::X_HAT + ml::Y_HAT));
(testvec2 += testvec3) += testvec3;
assert(testvec2.x == 1.f);
assert(testvec2.y == 3.f);
```

Output dir: task6/

## Products and Such

Next up are the dot product, cross product, and magnitude (or distance, or length, or norm, or whatever you wish to call it). I've done the function signatures:

```cpp
constexpr auto dot(vector3d const v1, vector3d const v2) -> float {
  //return ...something;
}

constexpr auto cross(vector3d const v1, vector3d const v2) -> vector3d {
  //return ...something;
}

inline auto magnitude(vector3d const v) -> float {
  // return ...something;
}
```
You may have noticed that `magnitude()` (pop! pop!) is `inline` instead of `constexpr`. That's because you'll most likely need to use functions from the standard library that aren't constexpr themselves. Obviously we cannot have a compile-time function that calls other functions at runtime. 

The rest is up to you. Here's a hint for the magnitude: `std::sqrt` for calculating the square root is located in the standard header `<cmath>`. Another hint: square root might be the first time you'll need to use an epsilon for your equality comparison. Here's an example of one I wrote using the testvec2 from the last task:

```cpp
assert(std::abs(ml::magnitude(testvec2) - std::sqrt(10)) < 0.000001f);
```

Good luck.

Output dir: task8/

## Output
The reward of visual feedback is a great motivator, so let's do some work with output. Since it's ubiquitous nowadays, we'll write our output in JSON. Right now we only have 3D vectors, but we'll extend that in a moment. So how should we represent our vector in JSON? One way would be 1:1 with our data structure:

```json
{ 
    "x": 1.23456,
    "y": 7.89102,
    "z": 3.14159
}
```

If you prefer that sort of output, by all means implement it that way. But I find it a bit verbose for this task, so let's output it as an array:

```json
[1.23456, 7.89102, 3.14159]
```

To keep things clean and not pollute our vector3d.h with a bunch of json stuff, let's keep all our serialization (reading/writing from persistent storage) separate. Create a new header file called tojson.h and add:

```cpp
#pragma once
#include <string>
#include "vector3d.h"

namespace mymathlib::serialize {

        // serialize a vector3d as a json array of its components
        inline auto to_json(vector3d const& v) -> std::string {
                return "[" + std::to_string(v.x) + ", "
                        + std::to_string(v.y) + ", "
                        + std::to_string(v.z) + "]";
        }
}
```

As before with vector3d.h we start with `#pragma once` to avoid multiple inclusion. After that we include the standard string header as well as the header where our vector3d struct resides. Further down we put everything in a new namespace *inside* of our existing mymathlib namespace. In older code you might see

```cpp
namespace mymathlib {
    namespace serialize {
        ...code goes here
    }
}
```

But who has time to track down all of those closing curly-braces and make sure indentation is correct? I sure don't. If you prefer this style, go for it. There are definitely times (for example when doing a `using` or when forward declaring) when it makes sense, so it's worthwhile learning both.

I've `inline`'d the function to_json because we're calling `std::to_string` to convert our `float` components into `std::string` and this isn't a compile-time operation. I've also `inline`'d it because we haven't gotten around to adding more .cpp files to a project yet.

The implementation is pretty straightforward. We want our output, a JSON array, to resemble `<left-bracket><float><comma><float><comma><float><right-bracket>`. The whitespace in our output is unimportant and only there for readability.

Now that that's out of the way let's test it. Go back to your `main()` function and create a `vector3d` we can run it on. I'm just reusing `testvec2` from before:

```cpp
// you may have heard that calling std::endl blindly is considered bad form. that may be true,
// but we won't concern ourselves with it now. that's really a forest-for-the-trees problem at
// this early point
std::cout << "testvec2 = " << ml::serialize::to_json(testvec2) << std::endl; 
```

Build and run it, and with any luck you should see something like:

```
testvec2 = [1.000000, 3.000000, 0.000000]
```

Next we're going to work on operations and commands, and then the output is going to get *a lot* more interesting.

Output dir: task9/

## Commands

So far we've defined the following functions (ignoring the operators):

```
magnitude(vector3d) -> float
dot(vector3d, vector3d) -> float
add(vector3d, vector3d) -> vector3d
subtract(vector3d, vector3d) -> vector3d
cross(vector3d, vector3d) -> vector3d
```

We have three functions that take two vector arguments and output a third vector, one function that takes two vector arguments and outputs a scalar float value, and one function that takes one vector argument and outputs a scalar float value.

I want you to imagine we have some sort of automaton that carries out these operations for us. A very simple robot with a microphone that we can bark commands at and it gives us a result. What would the language that this robot understands look like?

```
Valid commands: magnitude, dot, add, subtract, cross
Valid arguments: command-specific
Output from automaton: command-specific
```

Now imagine we're working on that piece of the puzzle between the microphone and the part of the robot that performs the operations. We have a speech recognizer and it tells us, "the first word is 'magnitude.'" What's our next step? What should we expect after that? Obviously, the next thing we should expect to hear is a vector (let's pretend for now that we agreed upon a way of 'speaking vectors').

In other words, we started off expecting any sort of command from a list of valid ones, encountered a command we recognized, and entered a new state where we narrow down what kind of things we accept from the microphone. Can someone say, "magnitude pi", for example? No, pi is not a vector. Can they say "magnitude subtract"? No. At least not according to what we decided upon above.

If we wanted to describe this transition between states in pseudocode we could write something like:

```cpp
	auto const next_word = get_next_word(input);
	if (next_word == "magnitude") {
		auto const argument = expect_vector_or_fail(input); // anything but vector is an error
		expect_end_of_command_or_fail(input); // magnitude does not accept multiple arguments
	}
```

How would it look for, say, cross?

```cpp
	auto const next_word = get_next_word(input);
	if (next_word == "magnitude") { 
		...unimportant
	} else if (next_word == "cross") {
		auto const argument1 = expect_vector_or_fail(input);
		auto const argument2 = expect_vector_or_fail(input);
		expect_end_of_command_or_fail(input);
	}
```

Now we're getting somewhere. We haven't addressed the return types of these operations yet (and we haven't written any of these functions yet, so nothing will compile anyway), but this robot's speech processor is slowly starting to take shape.

Don't add it to any of the source code, but for the end of this task, I want you to finish the if-else code above for all of the commands we support so far and save it in a text file in the output directory. Don't forget the error cases (and ask yourself what happens in your pseudocode if `next_word` isn't recognized at all).

Output dir: task10/

## A Command Processor

We won't actually work with microphones and robots, but it's a nice analogy. We *will* be working with an input stream and we'll need to write a command parser/processor to figure out what commands to run and then run them.

I guess now is as good a time as any to make this project a little larger and add a second .cpp file. In Visual Studio you do this by right-clicking on the project and choosing Add -> New File. Follow the wizard and create `processor.cpp` and `processor.h`. If you're working in Xcode the process is similar. If you're doing all of this on the command-line with g++ or clang, and you don't already have a CMakeLists.txt or Makefile and don't know how to compile multiple .cpp files at the same time, then just use a simple shell script with something like:

```sh
echo "g++ -std=c++17 main.cpp processor.cpp -o vectorrobot" > build.sh && chmod +x build.sh;
```

and build with `./build.sh`. 

*Side Note: before the complexity of your projects grows too much, I'd encourage you to either use an IDE like VS/Xcode/KDevelop or if you want to look cool and hip use CMake with VSCode. People don't use those because they're morons who need a GUI to hold their hand. They use them because real-world projects get very large very fast and nobody wants to have a million system and 3rd party library datatypes and function signatures memorized or have to manually enter gdb commands to step through 80 function templates from `std::map`.*

When that's done, open up `processor.h` (not .cpp!) and add this standard boilerplate stuff:

```cpp
#pragma once
#include <iosfwd>

namespace mymathlib::processor {

}
```

Wait, what's iosfwd, you're probably wondering? Well, we haven't dealt with *how* we're going to get those command strings, but let's make this flexible and support both `std::cin` and `std::ifstream`. Both of those derive from a common base called `std::istream`, which is what we want to use. However, we don't want to force everyone `#include`ing our header to have to load the entire IO stuff from the standard library with it, so we use a different header called `iosfwd` that just has forward declarations of the types, but not their actual definitions.

Now, as a next step, switch to `processor.cpp` and add this:

```cpp
#include "processor.h"
#include <istream>

namespace mymathlib::processor {
}
```

We don't have anything yet, but that's OK. Go ahead and build, to make sure we didn't make any mistakes.

If we look back at the last task, we had pseudofunctions like `expect_vector_or_fail(input)` that took some mysterious input argument and returned a vector (or failed, if a vector wasn't encountered).

Now we need to think about how to actually write this pseudofunction in C++. What should the return type be? `vector3d` seems logical. But what about the error case where the next thing in `input` isn't a vector (or worse: `input` is EOF or in a bad state)? We *could* throw an exception, but I think it might be more fun to handle this a different way using a type you probably haven't encountered yet (no, sorry, it's not `std::expected`): `std::optional`.

`std::optional<T>` has one of two states: *either* it contains a value of type T which we can access with `.value()` *or* it contains the special value `std::nullopt`. Just a quick example of how to use it before we go on:

```cpp
  std::optional<int> x;
  assert(!x.has_value()); // x == std::nullopt
  x = 42;
  assert(x.has_value()); // x == 42
  std::optional<int> y;
  assert(!y.has_value()); // y == std::nullopt
  assert(x.value() + y.value_or(17) == 59); // 42 + 17
```

I hope that was clear because I don't intend to write a `std::optional` tutorial here. Please look it up in the documentation for more information if you need it.

Back to our commands, *one* (but not the only) way we could handle the parsing of a vector is then like this:

```cpp
#include <iosfwd>
#include <optional>

namespace mymathlib {

// here we forward-declare vector3d so we don't need to include "vector3d.h"
struct vector3d;

namespace processor {

using maybe_vector3d = std::optional<vector3d>;

auto expect_vector_or_fail(std::istream& input) -> maybe_vector3d;

...continued
```

And in our command-handling code we could do:

```cpp
if (next_word == "magnitude") {
	if (auto const argument = expect_vector_or_fail(input); argument.has_value()) {
		expect_end_of_command_or_fail(input); // magnitude does not accept multiple arguments
	} else {
		// note: this error SUCKS! we're not even showing a line # and
		// the input might contain millions of magnitude commands
		report_error("expected a vector after magnitude"); 
		return false;
	}
}
```

If you learning C++ from an old(er) resource, you're probably not familiar with the `if (assignment; condition)` syntax above either. This is syntactic sugar that helps you write more compact if-else branches. It is not functionally any different from

```cpp
auto const argument = expect_vector_or_fail(input);
if (argument.has_value())
```

But now `argument` is outside of the scope of the `if` and might cause side effects. If you like this way of writing it, by all means keep doing so.

Additionally, you could just write:

```cpp
if (auto const argument = expect_vector_or_fail(input)) {
```

because in this specific instance we're dealing with a type (`std::optional`) that can be converted to bool. But that won't always be the case.

We can't forget to add this to our `processor.cpp` file:

```cpp
#include "vector3d.h" // needed because we only forward-declared the type in processor.h

namespace mymathlib::processor {

auto expect_vector_or_fail(std::istream& input) -> maybe_vector3d {
	return {};
}
```

This is very similar to the function declaration in `processor.h`, except now we need to write a function *definition* in processor.cpp. If we don't, and we try to call `expect_vector_or_fail` somewhere else, it will result in a linker error. The `return {};` that we added just returns a `std::nullopt` for now. We'll get to its implementation next.

Output dir: there is no expected output for this task. Just verify everything builds and push the changes to your sources
