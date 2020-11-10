**TODO for your task:** Edit the Text in italics with your text.

<hr>

# Feature Use Case

<hr>

**Use Case**: Program Termination

**Primary Actor**: User

**Goal in Context**: To terminate the execution of the program.

**Preconditions**: The program must be running and in a responsive state.

**Trigger**: (1) Pressing the escape key. (2) Hitting the 'x' in the titlebar if avilable.
  
**Scenario 1**: A user will press the escape key when they are done painting.

**Scenario 2**: A user will drag their mouse to the top-right corner of the titlebar and left-click to exit the program.
 
**Exceptions**: The program may become potentially unresponsive. In this case, the program can be terminated from the operating system.

**Priority**: High-priority.

**When available**: First release

**Channel to actor**: The primary actor communicates through I/O devices. This includes the keyboard and the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of any keyboard event. The user is responsible for all other input.

**Secondary Actor**: N/A

**Channels to Secondary Actors**: N/A

**Open Issues**: We may need to implement 'saving' functionality in the future, and revise this use case to prompt a user with a save dialog before exiting (or even save ocassionally while drawing).

<hr>


(adapted by Pressman and Maxim, Software Engineering: A Practitioner’s Approach, pp. 151-152, from Cockburn,
A., Writing Effective Use-Cases, Addison-Wesley, 2001)
