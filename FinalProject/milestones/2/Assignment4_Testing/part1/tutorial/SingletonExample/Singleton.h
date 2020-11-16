/** 
 *  @file   Singleton.h
 *  @brief  Singleton Interface
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/
#include <vector>
#include <string>
// An example singleton class
class Log{
private:
	Log();
	
	// Static member variables
	static Log* _instance;
	static std::vector<std::string> messages;
	
public:
	
	// Static member functions
	static Log& Instance();
	static void AddStringToLog(std::string s);
	static void PrintLog();

};
