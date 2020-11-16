# Part 2 - Catch2

<img align="right" width="200px" src="./media/Catch22.jpg">

Now that we have our project files setup for our platform, and have done some refactoring, we can start to test our software. This again becomes very important as we want to write software that runs on multiple platforms. There exist many testing frameworks in our software that we can work with, and for this assignment we are going to use a popular framework called [Catch2](https://github.com/catchorg/Catch2). Catch2 is probably the simplest framework to setup, but is incredibly powerful for commercial applications.

# Resources to help

Provided below are a list of curated resources to help you complete the task(s) below. Consult them (read them, or do ctrl+f for keywords) if you get stuck.

1. For Task 1 - Catch2
	- Documentation on Catch2.
		- https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
	- Talk on Catch 2 (From the creator)
		- https://www.youtube.com/watch?v=Ob5_XZrFQH0
	

# Task 1 - Writing a Test

We have previously looked at writing tests before. However, as projects scale, we do not want to write all of our test cases within the source code of our project. It can thus be useful to use a testing framework to exercise functionality of our program.

## Catch2

[Catch2](https://github.com/catchorg/Catch2) is a great framework to get started with. The two main components are a 'TEST_CASE' and what you want to check using a macro called `REQUIRE` where we can validate that some condition is true.

A commented example of writing a TEST_CASE is found below:

```cpp
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
			   // You will only do this in one cpp file,
			   // even if you have multiple .cpp files in your
			   // test suite.
#include "catch.hpp"	   // Here is the 'catch.hpp' file. You can download
		           // it from the Catch2 github and put it in your 
			   // 'tests' directory.


/*! \brief A simple factorial function 
*/
unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

/*! \brief Test cases for factorial.
*/
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
```

## Your Task

- [ ] Downoad Catch2 now from: https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp
	- This is a single header file you can drop in your include directory.

### Testing our project

Now, any time we learn a new tool, we should practice with a simple example to get things up and running. Here is one version of how you might write a test case (without our refactored Singleton App class) in our actual project. You can create this source file called 'tests/main_test.cpp' in the 'part1/tests' directory.

```cpp
/** 
 *  @file   main_test.cpp 
 *  @brief  Unit Tests for our program
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Include our Third-Party SFML header
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
// Include standard library C++ libraries.
#include <iostream>
#include <string>
// Project header files
#include "App.hpp"
#include "Command.hpp"
#include "Draw.hpp"


void initialization(void){
	std::cout << "Starting the App" << std::endl;
}
 
/*! \brief 	Initialize and destroy the program
*		
*/
TEST_CASE("init and destroy"){	
	App::Init(&initialization);
	// Destroy our app
	App::Destroy();
}
```

#### Is this a good test?

Now the next question that comes up is to ask ourselves if the above is a good test?  In a good test, we should know:

1. If the TEST_CASE passed or failed (We can use the REQUIRES clause)
2. That the TEST_CASE eventually terminates (i.e. do not call functions with inifinite loops in them). 

### Incorporating Catch2 with CMakeLists.txt

Okay, so now that we have a test we will want to prepare to run it. The problem is, we don't have a way to build our project quite yet that is going to exercise the tests! So in order to build a separate project that runs a test suite, we can simply add another CMakeLists.txt file in the tests directory. We can alternatively modify our CMakeLists.txt file in the root of the part1 directory in order to automatically generate our tests as well. This means every time we build our program (and any libraries etc.) we can also build and run the associated tests with the project. 

**Modified CMakeLists.txt** in the part1 directory.

```
# This time what is new is I have added:
# 1.) another 'add_executable'
# 2.) another 'target_link_libraries'
#
# Observe now you will have two projects setup.
# As they stand, they will be identical.
####################################################
# The minimum required version of CMake to ouse
cmake_minimum_required(VERSION 3.10)

# Set the project name to your project name
project(App)

# Where are the include directories
include_directories("/usr/include/")
include_directories("./include/")

# Where are the libraries
# Hint: On linux you can grep for them: ldconfig -p | grep sfml
link_directories("/usr/lib/x86_64-linux-gnu/")

# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
add_executable(App ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./src/main.cpp)

add_executable(App_Test ./src/App.cpp ./src/Command.cpp ./src/Draw.cpp ./tests/main_test.cpp)

# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp
target_link_libraries(App sfml-graphics sfml-window sfml-system)
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system)
```

You will know this worked if you see both projects built, and when you run your App_Test, you see the single test case pass.

```bash
mike@system76-pc:~/temp2/monorepo-template/Assignment3_Testing/part1$ make
[ 10%] Building CXX object CMakeFiles/App.dir/src/App.cpp.o
[ 20%] Building CXX object CMakeFiles/App.dir/src/Command.cpp.o
[ 30%] Building CXX object CMakeFiles/App.dir/src/Draw.cpp.o
[ 40%] Building CXX object CMakeFiles/App.dir/src/main.cpp.o
[ 50%] Linking CXX executable App
[ 50%] Built target App
[ 60%] Building CXX object CMakeFiles/App_Test.dir/src/App.cpp.o
[ 70%] Building CXX object CMakeFiles/App_Test.dir/src/Command.cpp.o
[ 80%] Building CXX object CMakeFiles/App_Test.dir/src/Draw.cpp.o
[ 90%] Building CXX object CMakeFiles/App_Test.dir/tests/main_test.cpp.o
[100%] Linking CXX executable App_Test
[100%] Built target App_Test
mike@system76-pc:~/temp2/monorepo-template/Assignment3_Testing/part1$ ./App_Test 
===============================================================================
test cases: 1 | 1 passed
assertions: - none -
```

**Additional CMakeLists.txt** in the part1/tests directory.

Eventually, your project may get quite cluttered if you have multiple executables building within one CMakeLists.txt file. So instead you may explore the 'add_subdirectory' command, and utilize the separate CMakeLists file in the test directory. For now, this is optional.

## Your Task

Create a separate directory called 'part1/tests' in your project, and write 4 TEST_CASE's in the main_test.cpp for our program using the refactored application (i.e. without the Singleton). The test cases should exercise functionality of the actual classes you have implemented (e.g. draw, command, etc.)

## Requirements

- You have at least four non-trivial test cases.
	- Non-trivial means you are exercising some functionality in your Command, Draw, or App classes, and not simply checking (1==1) in your tests.
	- Note: Testing graphics applications can be tricky, but you can retrieve pixel colors for example to check if your command executed.
		- And a final note--perhaps now you will understand that implementing everything as a 'command' allows additional flexibility for automating tests. :)

## Testing

- Task 1
	- (You write the tests)

# Submission/Deliverables

- A main_test.cpp file in part1/tests with at least 4 test cases

### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary.

### Deliverables

- Task 1
	- Create at least 4 unit tests in  your project.
	- It is acceptable to add additional code to your project (functionality like 'getPixelColor') if you want to write more in-depth tests.


# Going Further

An optional task(if any) that will reinforce your learning throughout the semester--this is not graded.

- Try scaling up your test cases (https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#scaling-up) such that they are not written all in one file.

# F.A.Q. (Instructor Anticipated Questions)

1. Q: Can we use Google test?
   - A: Sure, but it's slightly harder to support. It will be a little bit easier however to use Catch2, as Catch2 is merely a single header file that you include in your project. I actually spent quite a bit of time configuring gtest and google Mock to see if it was appropriate for this course, but Catch2 will be the right tool for the right job for this course.
   	- Here are some further resources. 
   	- Google Test
		- Documentation on Google Test
			- https://github.com/google/googletest/blob/master/googletest/docs/primer.md
		- Main github page for Google Test
			- https://github.com/google/googletest
