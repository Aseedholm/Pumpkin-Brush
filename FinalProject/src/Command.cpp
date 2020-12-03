/** 
 *  @file   Command.cpp 
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
// Project header files
#include "Command.hpp"

/*! \brief 	N/A
*		
*/
Command::~Command(){
}

std::string Command::getCommand() {
     return m_commandDescription;
}

sf::Uint32 Command::getX() {
    return x;
}

sf::Uint32 Command::getY() {
    return y;
}

sf::Uint32 Command::getCanvasColor(){
    return canvasColor;
}
sf::Uint32 Command::getBrushColor(){
    return brushColor;
}
sf::Uint32 Command::getBrushType() {
    return brushType;
}

sf::Uint32 Command::getBrushSize() {
    return brushSize;
}

sf::Uint32 Command::getWindowX() {
    return windowX;
}
sf::Uint32 Command::getWindowY(){
    return windowY;
}