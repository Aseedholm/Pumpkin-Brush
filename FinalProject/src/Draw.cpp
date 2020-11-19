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
#include <vector>



/*! \brief 	Execute the command to draw a pixel
*
*/
bool Draw::execute() {
	for(int i = 0; i < m_sharder.size(); i++) {
        m_app->GetImage().setPixel(m_coordinate.x + m_sharder[i][0], m_coordinate.y + m_sharder[i][1], m_color);
    }

	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/
bool Draw::undo() {
    for(int i = 0; i < m_sharder.size(); i++) {
        m_app->GetImage().setPixel(m_coordinate.x + m_sharder[i][0], m_coordinate.y + m_sharder[i][1], m_originalColors[i]);
    }
	return true;
}

/*! \brief Get the original color of each pixels
 *
 */
void Draw::setOriginalColor() {
    for(int i = 0; i <m_sharder.size(); i++) {
        sf::Color pixelColor = m_app->GetImage().getPixel(m_coordinate.x + m_sharder[i][0], m_coordinate.y + m_sharder[i][1]);
        m_originalColors.push_back(pixelColor);
    }
}

/*! \brief 	Draw Constructor that takes in the x and y co-ordinates of the mouse
*
*/
//Draw::Draw(sf::Vector2i coordinate, App* app) {
Draw::Draw(sf::Vector2f coordinate, App* app) { //andrew edit **
	m_coordinate = coordinate;
	m_app = app;
	//m_brush = m_app->GetBrush();
	m_sharder = m_app->GetBrush().getShader();
	m_color = m_app->GetBrush().getColor();
    setOriginalColor();
}

