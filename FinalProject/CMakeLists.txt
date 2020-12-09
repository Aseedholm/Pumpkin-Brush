####################################################
# CMake is a build file generator.
# It does not compile your software, but
# rather uses the CMake Language to
# figure out how to generate another file
# for which you can then use to build projects.
# CMake is a specification language for build tools.
####################################################

############### INSTALLATION #######################
# Installation on Mac
# 'brew install cmake'
#
# Installation on Linux
# 'sudo apt-get install cmake'
#
# Installation on Windows
# See download page and download
####################################################

############## How to use CMake ####################
# I recommend you create a separate directory for
# your CMake generated files. This is a clean way
# to separate out all of your binary files generated
# from the source code. An example on Linux is
# the following:
#
# mkdir bin	# Make a directory
# cd bin	# navigate to that directory
# cmake .. 	# Then execute the CMakeLists.txt
#		# file found one directory up.
####################################################

####################################################
# Writing a CMake file involves writing one
# cmake command per line.

# The minimum required version of CMake to use
cmake_minimum_required(VERSION 3.10)

# Set the project name to your project name
# Additionally, we specify the languages we need
# to use with our project 'App' which happen
# to be 'C++' (CXX), and 'C' is also included
# just in case we mix C in our C++ code
project(
    App             # Name of our application
    VERSION 1.0     # Version of our software
    LANGUAGES CXX)  # Language that we are using

# We can additionally set the langauge standard for
# C++
set(CMAKE_CXX_STANDARD 17)

# Where are the include directories
#include_directories("/usr/local/include/")
#include_directories("include")
include_directories("/usr/include/")
include_directories("./include/")


#find_package(SFML REQUIRED COMPONENTS audio network graphics window system)


# Where are the libraries
# Hint: On linux you can grep for them: ldconfig -p | grep sfml
#link_directories("/usr/local/lib/")
link_directories("/usr/lib/x86_64-linux-gnu/")

# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
#
# Here is an example below adding multiple files

add_executable(App src/App.cpp src/Draw.cpp src/Command.cpp src/main.cpp src/BrushFactory.cpp

src/Brush.cpp src/Pen.cpp src/Erase.cpp src/Clear.cpp src/Gui.cpp) # example with more files
add_executable(Server src/Server.cpp)
add_executable(App_test ./src/App.cpp ./src/Draw.cpp ./src/Command.cpp
     ./src/Brush.cpp ./src/BrushFactory.cpp ./src/Erase.cpp ./src/Pen.cpp ./src/Clear.cpp ./src/Gui.cpp
      ./tests/src/main_test.cpp)


# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp
target_link_libraries(App sfml-graphics sfml-window sfml-system sfml-network GL)
target_link_libraries(Server sfml-graphics sfml-window sfml-system sfml-network pthread)
target_link_libraries(App_test sfml-graphics sfml-window sfml-system sfml-network GL)
