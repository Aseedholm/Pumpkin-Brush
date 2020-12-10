# Building Software

- [ ] Instructions on how to build your software should be written in this file
	- This is especially important if you have added additional dependencies.
	- Assume someone who has not taken this class (i.e. you on the first day) would have read, build, and run your software from scratch.
- You should have at a minimum in your project
	- [ ] A CMakeLists.txt in a root directory
    	- [ ] This should generate a 'release' version of your software
  - [ ] Run your code with the latest version of cppcheck before commiting your code (could be a github action)
  - [ ] (Optional) Run your code with the latest version of clang-tidy  (could be a github action)


## Building the Software Tutorial in an Ubuntu Linux environment

https://github.com/Fall20FSE/finalproject-pumpkin-brush.git
 
1. If you have not yet please clone the github repository located at the above github repository. 

2. After you have cloned it please navigate through the folder directory as follows

	- finalproject-pumpkin-brush => FinalProject => bin. 

3. Once you are inside the bin directory please run the following command [cmake ..] in a terminal opened at this location directory without the brackets. 

	- This will generate a makefile. 
4. While still in the bin directory in the terminal run the [make] command, once again without the brackets.

	- This will build the program binary files. It will create a Server binary and a Client binary. 

5. Now please open another two terminal tabs or terminals all located in the same bin directory. 

6. In one of the three terminals open please enter in [./Server port#] with port# being the numerical port number you wish the Server to be listening at (it must be a positive integer). 

	- Leave this Server running for as long as you would like to use the program. 

7. Next in the remaining two terminals enter [./App port#] with the port# matching the port number passed to Server (it must be a positive integer and if it doesn’t match the Server’s port number the networking will not function). 

	- This will establish a connection between the Client application, where we will actually do the drawing, and the Server program which receives commands from clients. 
	
8. Now feel free to play with the application as it will be open once the [./App port#] has been entered on the command line!

