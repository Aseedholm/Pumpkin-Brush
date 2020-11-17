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
// Project header files
#include "Command.hpp"

// Anytime we want to implement a new command in our paint tool,
// we have to inherit from the command class.
// This forces us to implement an 'execute' and 'undo' command.
class Draw : public Command{
private:
//	sf::Vector2i m_coordinate;
	sf::Vector2f m_coordinate; //andrew edit ***

	sf::Color m_originalColor;
	App* m_app;
public:
	bool execute();
	bool undo();
//	Draw(sf::Vector2i m_coordinate, App*);
	Draw(sf::Vector2f coordinate, App* app); //andrew edit ***
};

#endif
