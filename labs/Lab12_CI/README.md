# Lab 12

> "Continous Integration"

<img src="./media/actions.png" width=450px align="right">

For your lab today, you will be working in github to implement continuous integration features supported by the platform.

# Implementation Logistics

- You may use whatever operating system, IDE, or tools for completing this assignment.
	- However, my instructions will usually be using the command-line, and that is what I will most easily be able to assist you with.
- In the future there may be restrictions, so please review the logistics each time.

# Resources to help

Provided below are a list of curated resources to help you complete the tasks below. Consult them (read them, or do Ctrl+f for keywords) if you get stuck.

- Task 1
	1. Github Actions
		- Introduction to Github Actions video (12:32)
    			- https://www.youtube.com/watch?v=-xIXFxuZCMI
		- Introduction to Github Actions (38:46)
			- https://www.youtube.com/watch?v=e_F_4OB9Mg4
		- Github Actions Documentation
			- https://help.github.com/en/actions
 
# Task 0 - Find your team!

**Remember** You are working with your team today in your team repository.

# Task 1 - Continuous Integration

[Github actions](https://github.com/features/actions) are githubs built-in way of providing a continuous integration testing system for your project. Other technologies like Jenkins and Travis exist, though having all of the features located in one spot will make it easy for us to get started. Github actions are also very powerful in what you can do. Today you are going to setup in [../../../finalproject-pumpkin-brush/.github/workflows/MainWorkflow.yml](../../../finalproject-pumpkin-brush/.github/workflows/MainWorkflow.yml) your first workflow that will execute tests every time you push code. In this way, github actions will help ensure that code that you are submitting to your repository for example, is code that actually compiles and passes all of the tests. you have in the project.

Provided below is a working C/C++ continuous integration workflow file that will run as a 'github' action everytime you push your code to the master branch. You may implement or modify this for your needs.

```bash
# A simple C/C++ Continuous Integration file
name: C/C++ CI

# This action is pushed on any push to a specific branch,
# in this case, the master branch, although you could add others.
on:
  push:
    branches: [ main ]
    
# Every github action needs at least one job.
# We could have multiple jobs, but for now I am only going to include one here.
jobs:
  build_and_test: # This is the name of our job, and you will see it in the 'Actions' tab.
    # We can have our integration tests run on multiple operating systems in 'containers'
    # that are hosted on github. You can create your own as well, or setup a 'container'
    # using a tool like docker if you like. For now, I am going to show you the ubuntu setup.
    # Available environments are here: https://github.com/actions/virtual-environments
    runs-on: ubuntu-18.04
    # These are the steps that will be run every time that we run our script, one will follow
    # the other.
    # You can pretend you would be manually be typing these out in the terminal everytime you did
    # a 'push' before.
    steps:
      - uses: actions/checkout@v2
      - name: Quick check to see where we are and who we are.
        run: pwd && whoami && ls -l
      # For us, we need to setup our linux box which only takes a few moments
      - name: Update packages on linux
        run: sudo apt-get update
      - name: Install sfml
        run: sudo apt-get install libsfml-dev
      - name: build main.cpp code
        run: cd ./labs/Lab12_CI && g++ main.cpp -o main
      - name: run main
        run: cd ./labs/Lab12_CI && ./main
      - name: Build lab makefile
        run: cd ./labs/Lab12_CI/bin && cmake ..
      - name: Run lab12 makefile
        run: cd ./labs/Lab12_CI/bin && make
      # These next two steps need a little bit more explaining, because as we are finding out
      # testing graphics applications is really hard!
      # You learned this when you wrote your GUI applications tests earlier.
      # First and foremost, make sure your tests terminate at some point, otherwise they will run forever
      # and we will never finish this test!
      # Second, since we are running our code on github.com, we do not have a 'window', so we need
      # to install some tools that emulate having an actual desktop window to run our program in.
      # 'xvfb ' is one such tool, and you can see how I have set it up below.
      - name: Setup headless x11 window
        run: sudo apt-get install xvfb xorg xauth openbox # xorg is needed to set DISPLAY variable later
      - name: Run graphical application tests in headless mode
        run: cd ./labs/Lab12_CI/bin && xvfb-run --server-args="-screen 0 1024x768x24" ./App_Test
```

### Expanding on the workflow

Making sure your code compiles and passes tests is one thing, but we can also incorporate some of the other tasks that we have done throughout the semester. As an example, you can add a 'linter' or style checker to your code. For your task, you will have cppcheck automatically run on all of the ./src files (`cppcheck ./src/*.cpp`)

### Your task

1. Create and optionally modify a github workflow that runs everytime you attempt to push code into the repository.
	- A common modification is to have a separate 'actions' branch that only runs actions on code in that section, or perhaps to have individual actions in each team members individual branches that run before merging code.
2. Modify the workflow to run cppcheck as one of the steps

## Testing

- Look on your team repository under the 'Actions' tab, and ensure that at least one action has been run.

# Submission/Deliverables

- Task 1
  - We will look to see you have at least one workflow implemented and there was at least 1 Action.
  - We will look to see that you have a workflow for installing and running cppcheck on your ./src directory.
	
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

1. Create additional github actions for when you commit code.

# F.A.Q. (Instructor Anticipated Questions)

1. Q: Can I do X/Y/Z with Github Actions?
	- A. Take a quick peak at the documentation. Github actions are relatively new at the time of writing, and I imagine more features could be added before the course ends. You might want to consider further researching 'docker' and thinknig about the possibility of setting up testing on windows and mac platforms.
