#include <vector>
#include <numeric>

#define M_PI 3.1415

// Dummy structure
struct object{
	double radius;	
};

// Intentionally terrible code.
std::vector<object> pipes;
std::vector<object> hoses;

constexpr double area(const double r) {return r * r * M_PI;}

// This code will not compile (refactor 
double work(){
	
	// int value =0;
	// // step 1:
	// for(int i =0; i < pipes.size(); ++i){
	// 	value += pipes[i].radius * pipes[i].radius * M_PI;
	// }
	
	// // step 2:
	// for(int i =0; i < pipes.size(); ++i){
	// 	value += hoses[i].radius * pipes[i].radius * M_PI;
	// }

	const auto accumulate_area = [](const auto lhs, const auto rhs) {
		return lhs + area(rhs.radius);
	};

	const auto total_area = [&](const auto &container) {
		return std::accumulate(begin(container), end(container), 0.0, accumulate_area);
	};
	
	return total_area(pipes) + total_area(hoses); 
}

int main(){
	
	work(); //capture return type. 
	
	return 0;
}
