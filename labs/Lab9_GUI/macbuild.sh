# Simple build command for macOS
# Note the change here that we need to include OpenGL "-framework OpenGL"

# Use this as an example to just get things working (You may add additional flags like -std=c++17 for example)
clang++ main.cpp -o mygui -I./include/ -lsfml-graphics -lsfml-window -lsfml-system -framework OpenGL
