/**
 *  @file   Erase.hpp
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/
#include "Erase.hpp"
#include "App.hpp"

Erase::Erase(sf::Vector2f coordinate, App* app, int flag) : Command(flag) {
    m_coordinate = coordinate;
    m_app = app;
    m_backgroundColor = app->getBackgroundColor();
    m_shader = app->GetBrush().getShader();
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