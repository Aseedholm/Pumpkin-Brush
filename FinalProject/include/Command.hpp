/** 
 *  @file   Command.hpp 
 *  @brief  Represents an actionable command by the user.
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#ifndef COMMAND_HPP
#define COMMAND_HPP

// Include our Third-Party SFML header
// #include ...
// Include standard library C++ libraries.
#include <string>
#include <SFML/Network.hpp>
// Project header files
// #include ...

// The command class
class Command{
private:
	std::string m_commandDescription;
	//backgroundcolr
	//pencolor
	//pen type
	//pen size
	//x
	//y
	//window x
	//window y
	//+ getters 
	sf::Uint32 canvasColor;
	sf::Uint32 brushColor;
	sf::Uint32 brushType;
	sf::Uint32 brushSize;
	sf::Uint32 x;
	sf::Uint32 y;
	sf::Uint32 windowX;
	sf::Uint32 windowY;
	

public:
	
    int m_cmdFlag;
    // Constructor of a command
    Command(int cmdFlag, std::string m_commandDescriptionP, sf::Uint32 canvasColorP, sf::Uint32 brushColorP, int brushTypeP, int brushSizeP, int xP, int yP, int windowXP, int windowYP)
	: m_cmdFlag(cmdFlag), m_commandDescription(m_commandDescriptionP), canvasColor(canvasColorP), brushColor(brushColorP), brushSize((sf::Uint32)brushSizeP), x((sf::Uint32)xP), y((sf::Uint32)yP), windowX((sf::Uint32)windowXP), windowY((sf::Uint32)windowYP){};
	// Destructor for a command
	virtual ~Command();

	// Returns true or false if the command was able to succssfully
	// execute.
	// If it executes successfully, then that command is added to the
	// undo stack.
	// Each parameters also takes in a string name. While this may not be optimal,
	// it allows us to easily debug what each command is doing in a textual form.
	virtual bool execute() = 0;
	virtual bool undo() = 0;
	sf::Uint32 getCanvasColor();
	sf::Uint32 getBrushColor();
	sf::Uint32 getBrushType();
	sf::Uint32 getBrushSize();
	sf::Uint32 getX();
	sf::Uint32 getY();
	sf::Uint32 getWindowX();
	sf::Uint32 getWindowY();
	std::string getCommand();
};



#endif
