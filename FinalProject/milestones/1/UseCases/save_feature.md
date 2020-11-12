# Feature Use Case

**Use Case**: Save the current canvas image including all pixels on the canvas and export it as a image file (jpg, png, etc.).

**Primary Actor**: User

**Goal in Context**: Save the current image as a jpg or png file type, based on the current canvas state.

**Preconditions**: The program must be running and in a responsive state.

**Trigger**: Clicking the save feature in the toolbar or pressing s or ctrl + s.

**Scenario**: A user will left-click on the title bar and hit the save option (or hit the corresponding how key s, or ctrl + s) which will save export the current canvas as a set image type png or jpg.

**Exceptions**: If the program becomes unresponsive the image may not be saved or saved in a incorrect state.

**Priority**: Mid-priority

**When available**: First-release or second-release.

**Channel to actor**: The primary actor communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of a left-click mouse event. The user is responsible for all other inputs. The SFML library's image class is responsible for the exporting of the image.

**Secondary Actor**: N/A

**Channels to Secondary Actors**: N/A

**Open Issues**: Need to decide what image types to be able to save in, need to implement GUI that will include save feature. 
