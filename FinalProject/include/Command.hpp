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
// Project header files
// #include ...

// The command class
class Command{
private:
	std::string m_commandDescription;

public:
    int m_cmdFlag;
    // Constructor of a command
    Command(int cmdFlag, std::string m_commandDescriptionP): m_cmdFlag(cmdFlag), m_commandDescription(m_commandDescriptionP){};
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
	std::string getCommand();
};



#endif
