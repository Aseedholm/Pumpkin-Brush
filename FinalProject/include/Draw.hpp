/**
 *  @file   Draw.hpp
 *  @brief  Drawing actions interface.
 *  @author Mike and Jugal
 *  @date   yyyy-dd-mm
 ***********************************************/
#ifndef DRAW_H
#define DRAW_H

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
#include <vector>
// Project header files
#include "Command.hpp"
#include "GeneralBrush.hpp"


// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
class Draw : public Command{
private:
	sf::Vector2f m_coordinate; //andrew edit ***
	App* m_app;
	std::vector<std::vector<int>> m_shader;
	std::vector<sf::Color> m_originalColors;
    sf::Color m_color;


public:

	bool execute();
	bool undo();
	void setOriginalColor();
//	Draw(sf::Vector2i m_coordinate, App*);
	Draw(sf::Vector2f coordinate, App* app, int flag, std::string command); //andrew edit ***

};

#endif
