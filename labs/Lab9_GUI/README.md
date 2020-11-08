# Lab 9 

> "C++ Immediate Mode GUI"

<img src="./media/nuklear.gif" width=450px align="right">

For your lab today, you will work with your team, helping each other setup the nuklear.h GUI.

# Implementation Logistics

- You may use whatever operating system, IDE, or tools for completing this assignment.
	- However, my instructions will usually be using the command-line, and that is what I will most easily be able to assist you with.
- In the future there may be restrictions, so please review the logistics each time.

# Resources to help

Provided below are a list of curated resources to help you complete the tasks below. Consult them (read them, or do Ctrl+f for keywords) if you get stuck.

- Task 1
	1. GUI
		- SFML Windows
			- https://www.sfml-dev.org/tutorials/2.5/window-window.php
    	- Nuklear GUI
      		- Github page and documentation
			- https://github.com/vurtun/nuklear
		 
# Task 0 - Find your team!

**Remember** You are working with your team today in your team repository.

# Task 1 - Nuklear Immediate Mode GUI

The Nuklear Immediate Mode GUI is a relatively lightweight Graphical User Interface(GUI) programmed in C. The nuklear GUI itself is only a single header file(nuklear.h) which makes it relatively easy to import. There is additionally a header file so that we can conveniently work with the GUI in SFML. 

Today I have provided a sample for you to use and play around with. The best way to learn with nuklear is to modify the additional samples provided in the nuklear directory.

Provided in todays task is an SFML sample that draws two windows--1 for the paint program, and 1 for the GUI.

### Your task

0. Modify the build script to compile for your platform. 
	- Note: I have provided a linuxbuild.sh as an example which you can modify, though you can also use the sample [./nuklear/demo/sfml_opengl2/Makefile](./nuklear/demo/sfml_opengl2/Makefile) in the nuklear demo directory helpful.
	- Eventually you should incorporate this build into your final project in your CMakeLists.txt
1. Add 1 more color(e.g. Blue) to the GUI to change the color drawn on the SFML window.
2. Remove the unnecessary "Button" and "Compression" component from the GUI Window
3. (Optional) Cleanup the code to provide a cleaner abstraction for using the GUI.

## Testing

- Make sure every time you change a color the change is reflected on the SFML window.

# Submission/Deliverables

- Task 1
  - A modified [main.cpp](./main.cpp)
	
### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary.

# Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2. Both partners should commit the same code.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

# Going Further

An optional task(if any) that will reinforce your learning throughout the semester--this is not graded.

1. Use the color picker to select a color to paint in.

# F.A.Q. (Instructor Anticipated Questions)

1. Q: Nuklear GUI is not working on mac/windows/linux?
	- A See if you can build the files from the included nuklear directory. 
  - Use the 'Makefile' as a reference from the official repository.
  - Try the nuklear_sfml_gl3.h sample if nuklear_sfml_gl2 does not work (I suspect Mac users will need to use nuklear_sfml_gl2)

