/** 
 *  @file   Singleton.cpp 
 *  @brief  Singleton Implementation
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#include "Singleton.h"


// Global static pointer to ensure the instance of a single class.
// The syntax here is a little 'weird', but remember the '::' is the scope operator
// So we are accessing within a 'classes' scope one of the member variables.
//
// Aside--why do we need this?
// When we make something 'static' in C++, we are essentially making it a 'global' variable
// within a translation unit(i.e. a .cpp file), thus we need to 
Log* Log::_instance = nullptr;
std::vector<std::string> Log::messages;


// Constructor
Log::Log(){

}

// Access all member functions through the 'Instance'
// function.
Log& Log::Instance(){
	if(_instance==nullptr){
		_instance = new Log();
	}
	return *_instance;
}

// Add a message to the log.
void Log::AddStringToLog(std::string s){
	messages.push_back(s);
}

// Uses an iterator to go through the vector data structure.
// Example documentation can be found here:
//	http://www.cplusplus.com/reference/vector/vector/begin/
void Log::PrintLog(){
	for(std::vector<std::string>::iterator it = messages.begin();
		it != messages.end();
		++it){

		std::cout << *it << "\n";
	}	
}
