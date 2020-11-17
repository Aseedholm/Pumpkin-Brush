/**
 *  @file   Erase.hpp
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/
#include <iostream>
#include "Erase.hpp"
#include "App.hpp"

Erase::Erase(sf::Vector2f coordinate, App* app) {
    m_coordinate = coordinate;
    m_app = app;
    m_originalColor = app->getImage().getPixel(coordinate.x, coordinate.y);
    m_backgroundColor = app->getBackgroundColor();

}

bool Erase::execute() {
    m_app->getImage().setPixel(m_coordinate.x, m_coordinate.y, m_backgroundColor);
    return true;
}

bool Erase::undo() {
    m_app->getImage().setPixel(m_coordinate.x, m_coordinate.y, m_originalColor);
    return true;
}
