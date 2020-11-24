#include <iostream>
#include <string>

std::string get_value(){
	//Return the string value we are attempting to retrieve. 
	//Placeholder value used. 
	 return "Hello World";
}

int main(){
	
	// std::string value;
	
	// get_value(value);

	const auto value = get_value();
	
	return 0;
}