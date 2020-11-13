/**
 *  @file   Draw.cpp
 *  @brief  Draw implementation, all drawing actions are commands.
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

 // Include our Third-Party SFML header
#include <SFML/Graphics/Color.hpp>
// Include standard library C++ libraries.
// #include ...
// Project header files
#include "App.hpp"
#include "Draw.hpp"
#include <iostream>



/*! \brief 	Execute the command to draw a pixel
*
*/
bool Draw::execute() {
	// App::mouseX = x;
	// App::mouseY = y; 
	m_app->GetImage().setPixel(m_x, m_y, sf::Color::Blue);
	// std::cout<<x<<" "<<y;
	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/
bool Draw::undo() {
	m_app->GetImage().setPixel(m_x, m_y, sf::Color::White);
	return true;
}
/*! \brief 	Draw Constructor that takes in the x and y co-ordinates of the mouse
*
*/
Draw::Draw(unsigned int x, unsigned int y, App* app) {
	m_x = x;
	m_y = y;
	m_app = app;

}