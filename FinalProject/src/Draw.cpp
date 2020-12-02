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

	for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_color);
    }
	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/
bool Draw::undo() {

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
        std::cout << m_coordinate.x << " " << m_coordinate.y << std::endl;
        std::cout << m_shader[i][0] << " " << m_shader[i][1] <<std::endl;
        sf::Color pixelColor = m_app->getImage().getPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1]);
        std::cout << i << std::endl;
        m_originalColors.push_back(pixelColor);
        std::cout << i << std::endl;
    }
}

/*! \brief 	Draw Constructor that takes in the x and y co-ordinates of the mouse
*
*/
Draw::Draw(sf::Vector2f coordinate, App* app) { //andrew edit **
std::cout << "PRINT 1" << std::endl;
	m_coordinate = coordinate;
    std::cout << "PRINT 2" << std::endl;
	m_app = app;
    std::cout << "PRINT 3" << std::endl;
	m_shader = m_app->GetBrush().getShader();
    std::cout << "PRINT 4" << std::endl;
	m_color = m_app->GetBrush().getColor();
    std::cout << "PRINT 5" << std::endl;
    setOriginalColor();
    std::cout << "PRINT 6" << std::endl;
}

