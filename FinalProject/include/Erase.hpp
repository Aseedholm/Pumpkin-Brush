/**
 *  @file   Erase.cpp
 *  @brief  Implementation of Command.hpp
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

#ifndef APP_ERASE_HPP
#define APP_ERASE_HPP

#include <SFML/Graphics/Color.hpp>

#include "Command.hpp"
#include "App.hpp"

class Erase : public Command {
private:
    sf::Vector2f m_coordinate;
    sf::Color m_originalColor;
    sf::Color m_backgroundColor;
    App* m_app;

public:
    bool execute();
    bool undo();
    Erase(sf::Vector2f coordinate, App* app);
};


#endif //APP_ERASE_HPP
