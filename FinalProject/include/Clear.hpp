/**
 *  @file   Clear.cpp
 *  @brief  Draw implementation, all drawing actions are commands.
 *  @author Mike and ????
 *  @date   yyyy-dd-mm
 ***********************************************/

#ifndef APP_CLEAR_H
#define APP_CLEAR_H

#include "Command.hpp"
#include "App.hpp"

class Clear: public Command {
private:
    sf::Image* m_newImage;
    sf::Image m_originalImage;
    sf::Color m_backgroundColor;
    sf::Vector2u m_imageSize;
    App* m_app;

public:
    bool execute();
    bool undo();
    Clear(App* app); // class constructor
    ~Clear();
};

#endif //APP_CLEAR_H
