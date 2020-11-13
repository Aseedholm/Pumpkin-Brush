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
	unsigned int m_x;
	unsigned int m_y;
	sf::Color m_originalColor;
	App* m_app;
	public:
	bool execute();
	bool undo();
	Draw(unsigned int, unsigned int, App*);
};

#endif
