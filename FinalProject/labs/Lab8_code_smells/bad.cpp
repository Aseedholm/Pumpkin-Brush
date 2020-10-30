// Run with: clang-tidy bad.cpp -- -I./
// 
// First argument is the program
// Second is the file we want to analyze
// Third is the checks we want to run (-- is everything)
// Fourth is the include path to any file paths we included. 
//
#include <string>
#include <iostream>

void setup(){

        // (1) Hmm, should I deallocate this.
        int* memory = new int[50];
}

int main(){

        int a;

        // (2) This is bad
        if(a = 7){
                // Why, because we are doing assignment
                // instead of testing for equality.
        }


        return 0;
}
