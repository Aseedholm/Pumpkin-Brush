/**
 *  @file   Erase.hpp
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/
#include "Erase.hpp"
#include "App.hpp"

/*! \brief Constructor of erase command
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

/*! \brief Execute erase command
 *
 */
bool Erase::execute() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_backgroundColor);
    }
    return true;
}

/*! \brief Undo erase command
 *
 */
bool Erase::undo() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_originalColors[i]);
    }
    return true;
}

/*! \brief Get the original color when the erase command is constructed
 *
 */
void Erase::setOriginalColor() {
    for(int i = 0; i <m_shader.size(); i++) {
        sf::Color pixelColor = m_app->getImage().getPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1]);
        m_originalColors.push_back(pixelColor);
    }
}