/**
 *  @file   Clear.hpp
 *  @brief  This class represents a clear canvas command in the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/

#ifndef APP_CLEAR_H
#define APP_CLEAR_H

#include "Command.hpp"
#include "App.hpp"

/*! \brief Clear command
 *
 */
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
    Clear(App* app, int flag, std::string command); // class constructor
    ~Clear();
};

#endif //APP_CLEAR_H
