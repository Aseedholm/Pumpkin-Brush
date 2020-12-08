/**
 *  @file   Erase.cpp
 *  @brief  This class represents a pixel erasing command in the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/
#include "Erase.hpp"
#include "App.hpp"

/*! \brief The constructor of the Erase class.
 *
 */
Erase::Erase(sf::Vector2f coordinate, App* app, int flag, std::string command) : Command(flag, command) {
    m_coordinate = coordinate;
    m_app = app;
    m_backgroundColor = app->getBackgroundColor();
    dir_largeEraser = {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
        {-1, -2}, { -1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
        {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
        {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
        {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};
    m_shader = dir_largeEraser;
    setOriginalColor();
}


/*! \brief The destructor of the Erase class.
 *
 */

bool Erase::execute() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_backgroundColor);
    }
    return true;
}



/*! \brief Execute the erase pixel command.
 *
 */
void Erase::setOriginalColor() {
    for(int i = 0; i <m_shader.size(); i++) {
        sf::Color pixelColor = m_app->getImage().getPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1]);
        m_originalColors.push_back(pixelColor);
    }
}

/*! \brief Undo the erase pixel command and restore the pixels that were previously erased.
 *
 */
bool Erase::undo() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_originalColors[i]);
    }
    return true;
}