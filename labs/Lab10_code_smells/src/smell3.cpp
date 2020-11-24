// Compile with: g++ -std=c++11 smell3.cpp

#include <iostream>
#include <vector>
#include <algorithm> // added.

void process_more(const std::vector<double> &values) {
	for(const auto &v : values){
		std::cout << v << std::endl;
	}
}

// void process_more(const std::vector<double> &);

void process_data(const std::vector<double> &values){
	// bool in_range = true;
	
	// for(const auto &v : values){
	// 	if(v < 5.0 || v > 100.0){
	// 		in_range = false;
	// 		break;
	// 	}
	// }
	
	// if(in_range){
	// 	process_more(values);
	// }
	const auto in_range = [](const double d) {
		return d >= 5.0 && d<= 100.0;
	};

	const bool all_in_range = all_of(begin(values), end(values), in_range);

	if (all_in_range) {
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
