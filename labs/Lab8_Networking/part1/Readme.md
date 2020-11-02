# Part 1 - TCP


# Resources to help

Provided below are a list of curated resources to help you complete the task(s) below. Consult them (read them, or do ctrl+f for keywords) if you get stuck.


1. Networking
	- SFML Guide on networking
        - https://www.sfml-dev.org/tutorials/2.5/network-socket.php
    - SFML Guide on packets
        - https://www.sfml-dev.org/tutorials/2.5/network-packet.php
2. Youtube SFML Networking video
    - An 'okay' implementation of sockets in SFML
        - (Code works, but I would recommend studying my refactored examples instead)
        - https://www.youtube.com/watch?v=OSwutjvNjK4&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg&index=22
        

# TCP Networking

Review the above TCP Networking samples in SFML. The videos and documentation provide a nice crash course into networking. While it is not expected you will be an expert in networking, you should be able to understand the basics.

## Your Task

1. Get the TCP Code sample running, and make sure you understand the code Then look at part 2 and make a determination with your teammates, if you should use UDP or TCP protocol for the paint program.

## Testing

- Task 1
	- You should be able to use your [CMakeLists.txt](./CMakeLists.txt) file to generate a build file that can compile the code provided in the source directory.

# Submission/Deliverables

- Git add/commit/push your [CMakeLists.txt](./CMakeLists.txt) file.

### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary.

# Submission/Deliverables

- Task 1
	- Upload a screenshot of the TCP networking example code called [tcp.jpg](./tcp.jpg) to the repository.

	
### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary.

# Rubric

You (and any partner(s)) will receive the same grade from a scale of 0-2. Both partners should commit the same code.

- 0 for no work completed by the deadline
- 1 for some work completed, but something is not working properly
- 2 for a completed lab (with possible 'going further' options completed)

* Note: You must also commit any additional files into your repository so we can test your code.
  * Points will be lost if you forget!

# Going Further

An optional task(if any) that will reinforce your learning throughout the semester--this is not graded.

1. Refactor the networking code into separate client and server classes. 

# F.A.Q. (Instructor Anticipated Questions)

1. Q: The network is not working!
	- A: Try a different ip, try a different port number, perhaps try a different wifi(mobile hotspot instead of Northeastern's netwrok).

