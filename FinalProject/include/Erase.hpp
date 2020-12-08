/**
 *  @file   Erase.hpp
 *  @brief  This class represents a pixel erasing command in the mini paint app.
 *  @author Japher Su and Hao Zheng
 *  @date   2020-07-12
 ***********************************************/

#ifndef APP_ERASE_HPP
#define APP_ERASE_HPP

#include <SFML/Graphics/Color.hpp>

#include "Command.hpp"
#include "App.hpp"

/*! \brief Erase command
 *
 */
class Erase : public Command {
private:
    sf::Vector2f m_coordinate;
    sf::Color m_backgroundColor;
    std::vector<std::vector<int>> m_shader;
    std::vector<sf::Color> m_originalColors;
    App* m_app;
    std::vector<std::vector<int>> dir_largeEraser;

public:
    bool execute();
    bool undo();
    void setOriginalColor();
    Erase(sf::Vector2f coordinate, App* app, int flag, std::string command);
};

#endif //APP_ERASE_HPP
