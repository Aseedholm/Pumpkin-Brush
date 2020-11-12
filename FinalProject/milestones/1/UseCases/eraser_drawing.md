# Feature Use Case

**Use Case**: Erase pixels by left-clicking on a drawn area of the screen after selecting the erase feature.

**Primary Actor**: User

**Goal in Context**: Remove pixels from the canvas contained inside the program window.

**Preconditions**: The program must be running and in a responsive state

**Trigger**: Left-click of mouse on canvas after specifying an erase operation (button click/hotkey).

**Scenario**: A user will left-click on their mouse to erase a pixel after selecting the erase operation (may be clicking an icon), as long as the left-click takes place in the program window on the canvas and moves over drawn pixels those pixels should be erased.

**Exceptions**: If the program becomes unresponsive pixels may/will not be erased properly on the canvas and the program would have to be terminated.

**Priority**: Mid-priority

**When available**: First-release or second-release.

**Channel to actor**: The primary actor communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of a left-click mouse event. The user is responsible for all other inputs.

**Secondary Actor**: N/A

**Channels to Secondary Actors**: N/A

**Open Issues**: Need to implement erase feature and decide if a user can erase other user's pixels. 
