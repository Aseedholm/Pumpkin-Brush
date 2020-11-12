# Feature Use Case

**Use Case**: Concurrent Drawing

**Primary Actor**: User(s)

**Goal in Context**: Add multiple pixels to the canvas contained inside the program window when multiple users are drawing at the same time.

**Preconditions**: The program must be running and in a responsive state

**Trigger**: Left-click of mouse on canvas by each user.

**Scenario**: A user(s) will left-click on their mouse to draw pixels, as long as the left-click takes place in the program window on the canvas.

**Exceptions**: If the program becomes unresponsive pixels may/will not show up on the canvas and the program would have to be terminated.

**Priority**: High-priority.

**When available**: First-release

**Channel to actor**: The primary actor(s) communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of a left-click mouse event. The user(s) is responsible for all other inputs.

**Secondary Actor**: Other users

**Channels to Secondary Actors**: The secondary actor(s) communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of a left-click mouse event. The user(s) is responsible for all other inputs.

**Open Issues**: Properly getting multi-threading to work with the application and getting locks to lock data properly.
