/** 
 *  @file   main.cpp 
 *  @brief  Driver for the Singleton class
 *  @author Mike and ???? 
 *  @date   yyyy-dd-mm 
 ***********************************************/

#include "Singleton.h"

// Program Entry
int main(int argc, char* argv[]){

	Log::Instance().AddStringToLog("message 1");	
	Log::Instance().AddStringToLog("message 2");	
	Log::Instance().AddStringToLog("message 3");	

	Log::Instance().PrintLog();

	return 0;
}
