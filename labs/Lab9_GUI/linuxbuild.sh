# Simple build command for linux
# Notice that the -lGL command is new for linking in OpenGL
g++ main.cpp -o mygui -I./include/ -lsfml-graphics -lsfml-window -lsfml-system -lGL
