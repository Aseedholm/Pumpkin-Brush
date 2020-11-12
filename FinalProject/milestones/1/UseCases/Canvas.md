<hr>

# Use Case Canvas

<hr>

**Use Case**: Program initiation by displaying a 1920x1080 canvas

**Primary Actor**: Users

**Goal in Context**: To start the program and greet user with a white drawable canvas of dimensions 1920x1080 

**Preconditions**: The program must be running and in a responsive state

**Trigger**: Compile the program through command line and execute the binary executable file
  
**Scenario**: The user will compile the program on the command line and then will execute the binary file generated 
 
**Exceptions**: The program may not compile properly due to the errors in the code and hence the program won't start. In this case, user should check if she has the system configured properly including installations of necessary libraries.

**Priority**: High Priority

**When available**: First release

**Channel to actor**: The primary actor communicates through I/O devices. This includes the keyboard and the mouse. The system is responsible for compiling the program and executing the binary file. The user is responsible for all other input i.e. writing commands to execute the program.

**Secondary Actor**: N/A

**Channels to Secondary Actors**: N/A

**Open Issues**: We may want to eliminate the case where use compiles the code first, to make it look like a more finished product we can only provide user with an executable.

<hr>



(adapted by Pressman and Maxim, Software Engineering: A Practitioner’s Approach, pp. 151-152, from Cockburn,
A., Writing Effective Use-Cases, Addison-Wesley, 2001)
