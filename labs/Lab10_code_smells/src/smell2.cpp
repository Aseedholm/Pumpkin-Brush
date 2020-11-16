#include <iostream>
#include <string>

void get_value(std::string &out_param){
	 // mutate out_param in some way
	 // and because it is passed by reference
	 // we can re-use that value.
}

int main(){
	
	std::string value;
	
	get_value(value);
	
	return 0;
}