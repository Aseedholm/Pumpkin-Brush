/**
 *  @file   Erase.hpp
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/
#include "Erase.hpp"
#include "App.hpp"
//int canvasColorP, int brushColorP, int brushTypeP, int brushSizeP, int xP, int yP, int windowXP, int windowYP
Erase::Erase(sf::Vector2f coordinate, App* app, int flag, std::string command) : Command(flag, command, app->getBackgroundColor().toInteger(), app->getBrush().getColor().toInteger(), app->getBrush().getType(), app->getBrush().getSize(), coordinate.x, coordinate.y, app->getWindow().getSize().x, app->getWindow().getSize().y) {
    m_coordinate = coordinate;
    m_app = app;
    m_backgroundColor = app->getBackgroundColor();
    m_shader = app->getBrush().getShader();
    setOriginalColor();

}

bool Erase::execute() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_backgroundColor);
    }
    return true;
}

bool Erase::undo() {
    for(int i = 0; i < m_shader.size(); i++) {
        m_app->getImage().setPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1], m_originalColors[i]);
    }
    return true;
}

void Erase::setOriginalColor() {
    for(int i = 0; i <m_shader.size(); i++) {
        sf::Color pixelColor = m_app->getImage().getPixel(m_coordinate.x + m_shader[i][0], m_coordinate.y + m_shader[i][1]);
        m_originalColors.push_back(pixelColor);
    }
}


// std::string Erase::getCommand() {
//     return m_commandDescription;
// }

App* Erase::getOldApp() {
    return m_app;
}