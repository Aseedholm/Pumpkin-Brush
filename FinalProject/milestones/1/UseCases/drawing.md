# Feature Use Case

**Use Case**: Draw on canvas.

**Primary Actor**: User

**Goal in Context**: Add pixels to the canvas contained inside the program window.

**Preconditions**: Program must be running and in a responsive state.

**Trigger**: Left-click of mouse on canvas.

**Scenario**: A user will left-click on their mouse to draw pixels, as long as the left-click takes place in the program window on the canvas.

**Exceptions**: If the program becomes unresponsive pixels may/will not show up on the canvas and the program would have to be terminated.

**Priority**: High-priority.

**When available**: First release.

**Channel to actor**: The primary actor communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should response within 1 second of a left-click mouse event. The user is responsible for all other inputs.

**Secondary Actor**: N/A

**Channels to Secondary Actors**: N/A

**Open Issues**: When the title bar is left-clicked and the program window is moved, this can cause pixels to appear on the canvas area when the mouse pointer is not on the canvas itself.
