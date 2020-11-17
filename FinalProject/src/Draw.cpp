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
	m_app->GetImage().setPixel(m_coordinate.x, m_coordinate.y, m_app->GetBrush().getColor());
	// std::cout<<x<<" "<<y;
	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/
bool Draw::undo() {
	m_app->GetImage().setPixel(m_coordinate.x, m_coordinate.y, m_originalColor);
	return true;
}
/*! \brief 	Draw Constructor that takes in the x and y co-ordinates of the mouse
*
*/
//Draw::Draw(sf::Vector2i coordinate, App* app) {
Draw::Draw(sf::Vector2f coordinate, App* app) { //andrew edit **
	m_coordinate = coordinate;
	m_app = app;
	m_originalColor = app->GetImage().getPixel(coordinate.x, coordinate.y);

}
