// Compile with: g++ -std=c++11 smell3.cpp

#include <iostream>
#include <vector>

void process_more(const std::vector<double> &values){
	for(const auto &v : values){
		std::cout << v << std::endl;
	}
}

void process_data(const std::vector<double> &values){
	bool in_range = true;
	
	for(const auto &v : values){
		if(v < 5.0 || v > 100.0){
			in_range = false;
			break;
		}
	}
	
	if(in_range){
		process_more(values);
	}
}

int main(){
	
	std::vector<double> myVec;
	
	myVec.push_back(10.0);
	myVec.push_back(2.0);
	
	process_data(myVec);
	
	return 0;
}
