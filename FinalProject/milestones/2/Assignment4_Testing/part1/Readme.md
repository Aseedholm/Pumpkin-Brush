# Part 1 - Refactoring

We have previously solved some important software engineering challenges like how to create project files for multiple platforms. We can now work in the environment of our choice without any worries.

But how do we know our code works? We must rely on testing!

Umm, just one small problem...did you spot a major the design error in our program when it comes to rigorous testing?

# Resources to help

Provided below are a list of curated resources to help you complete the task(s) below. Consult them (read them, or do ctrl+f for keywords) if you get stuck.

- Task 1 
	- Talk on refactoring from Martin Fowler
		- https://www.youtube.com/watch?v=6wDoopbtEqk

# Task 1 - Refactoring

The Singleton pattern is a great one. It can be very convenient for having a 'managing' class that can be referenced everywhere in our code. One small problem however is that it is hard to work with testing infrastructure--especially if we are trying to incorporate many unit tests together.

In a previous lab you for instance described how you may approach testing a graphical program (i.e. our paint program). The problem is the Singleton class is very tightly coupled with our code, so it may interfere with our ability to run multiple tests easily in a unit testing framework. We want to instead decouple our Singleton class for a cleaner design.

## Your Task

- Refactor your code so that the Singleton pattern is no longer present in your code. That is, we should not see the 'static' qualifier in any of your member functions. You should instead instantiate an instance of your 'App' class in main.

### Tutorial Video

You can step into the [./tutorial](./tutorial) directory to see an example of how to refactor out a singleton class.

## Advice

- Refactor your code in the part1 directory slowly!
- Use your CMake generated build files to speed up your development by building your code as you make changes within your editor of choice. Again, you only need to re-run CMake when you need a new project to be generated.

## Testing

- Task 1
	- Grep your code (In the [/src](./src) directory) to see that 'static' is no longer present in the App class member variables or function signature.
	- Your drawing program should otherwise have the same exact behavior as the starter code provided before the refactoring.

# Submission/Deliverables

- Refactor the App class to remove the Singleton pattern. This may involve changes in other parts of the program as well (e.g. main.cpp)

# Going Further

An optional task(if any) that will reinforce your learning throughout the semester--this is not graded.

1. N/A

# F.A.Q. (Instructor Anticipated Questions)

1. Q: Should I be working in the part1 directory?
	- A: Yes, you do not have to copy things into part2.
2. Q: Do I need to incorporate my A2 assignment here?
	- A: No you do not
