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
	// App::mouseX = x;
	// App::mouseY = y;
	std::vector<std::vector<int>> shader = m_app->GetBrush().getShader();
	for(int i = 0; i < shader.size(); i++) {
        m_app->GetImage().setPixel(m_coordinate.x + shader[i][0], m_coordinate.y + shader[i][1], m_app->GetBrush().getColor());
        sf::Sprite sprite;
        

    }


	// std::cout<<x<<" "<<y;
	return true;
}

/*! \brief 	Undo command to undo the pixel creation
*
*/
bool Draw::undo() {
    std::vector<std::vector<int>> shader = m_app->GetBrush().getShader();
    for(int i = 0; i < shader.size(); i++) {
        m_app->GetImage().setPixel(m_coordinate.x + shader[i][0], m_coordinate.y + shader[i][1], m_originalColor);
    }
	return true;
}
/*! \brief 	Draw Constructor that takes in the x and y co-ordinates of the mouse
*
*/
//Draw::Draw(sf::Vector2i coordinate, App* app) {
Draw::Draw(sf::Vector2f coordinate, App* app) { //andrew edit **
	m_coordinate = coordinate;
	m_app = app;
	m_brush = m_app->GetBrush();
	m_originalColor = app->GetImage().getPixel(coordinate.x, coordinate.y);

}
