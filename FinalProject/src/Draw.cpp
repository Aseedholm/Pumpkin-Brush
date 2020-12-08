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



/*! \brief 	Execute the command to draw pixels
*
*/
bool Draw::execute() {

	for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_color);
    }
	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/

bool Draw::undo() {
    sf::Packet packetInDraw;
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_originalColors[i]);
    }
	return true;
}

/*! \brief Get the original color of each pixel
 *
 */
void Draw::setOriginalColor() {
    for(int i = 0; i <m_shader.size(); i++) {
        sf::Color pixelColor = m_app->getImage().getPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1]);
        m_originalColors.push_back(pixelColor);
    }
}

/*! \brief 	Constructor of draw command
*
*/
Draw::Draw(sf::Vector2f coordinate, App* app, int cmdFlag, std::string command) :Command(cmdFlag, command) { //andrew edit **
	m_coordinate = coordinate;
	m_app = app;
	m_shader = m_app->getBrush().getShader();
	m_color = m_app->getBrush().getColor();
    setOriginalColor();
}

