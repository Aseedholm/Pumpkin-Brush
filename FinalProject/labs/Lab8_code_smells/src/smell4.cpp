#include <vector>

#define M_PI 3.1415

// Dummy structure
struct object{
	float radius;	
};

// Intentionally terrible code.
std::vector<object> pipes;
std::vector<object> hoses;

// This code will not compile (refactor 
void work(){
	
	int value =0;
	// step 1:
	for(int i =0; i < pipes.size(); ++i){
		value += pipes[i].radius * pipes[i].radius * M_PI;
	}
	
	// step 2:
	for(int i =0; i < pipes.size(); ++i){
		value += hoses[i].radius * pipes[i].radius * M_PI;
	}
	
}

int main(){
	
	work();
	
	return 0;
}
