# Feature Use Case

**Use Case**: *Save the current canvas image including all pixels on the canvas.*

**Primary Actor**: *User*

**Goal in Context**: *TSave the current image as a jpg or png file type, based on the current canvas state.*

**Preconditions**: *The program must be running and in a responsive state*

**Trigger**: *Clicking the save feature in the toolbar.*
  
**Scenario**: *A user will left-click on the title bar and hit the save option which will save export the current canvas as a set image type png or jpg.*
 
**Exceptions**: *If the program becomes unresponsive the image may not be saved or saved in the correct state.*

**Priority**: *Mid-priority*

**When available**: *First-release or second-release*

**Channel to actor**: *The primary actor communicates through the I/O device, the mouse. The system is responsible for maintaining focus of the window when the user clicks, and should respond within 1 second of a left-click mouse event. The user is responsible for all other inputs.*

**Secondary Actor**: *N/A*

**Channels to Secondary Actors**: *N/A*

**Open Issues**: *Need to decide what image types to be able to save in.*

