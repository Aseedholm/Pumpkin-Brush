# Part 1 - More UDP Networking

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
        - https://www.youtube.com/watch?v=kOXiLUTivHw&list=PLHJE4y54mpC5j_x90UkuoMZOdmmL9-_rg&index=24
        

# More UDP Networking

Last time we looked at UDP and TCP Networks. Today I wanted to provide a fully working example with multiple clients. So here are a few brief notes:

1. In this example you are going to see a partially implemented client/server where a client sends messages to a server, and the server immediately broadcasts that data back to the clients.
2. The server stores all messages it has ever received. This could be useful for debugging, but it is also useful if a client needs to retrieve past history.
3. This example breaks the code into separate classes for the Server and the Client. It really is just an abstraction over SFML however to make integrating this into a codebase easier.
4. After understanding how sockets are just a way to transmit data, understand that the server and client could even be implemented in completely different programming languages! That is actually really cool!

## Your Task

1. Get the UDP Code sample running, and make sure you understand the code. 

## Testing

- Task 1
	- You should be able to use your [CMakeLists.txt](./CMakeLists.txt) file to generate a build file that can compile the code provided in the source directory.
		- Hint: If you have trouble debugging, try building with `cmake -DCMAKE_BUILD_TYPE=Debug ..`

# Submission/Deliverables

- Git add/commit/push your [CMakeLists.txt](./CMakeLists.txt) file.

### Submission

- Commit all of your files to github, including any additional files you create.
- Do not commit any binary files unless told to do so.
- Do not commit any 'data' files generated when executing a binary.

# Submission/Deliverables

- Task 1
	- Upload a screenshot of the UDP networking example code called 'udp.jpg' to the repository.

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

1. Refactor the networking code to handle custom packets. Some infrastructure is setup for you already if you like! Otherwise you could complete the final project by sending strings and parsing them, those having a custom packet will be much more clean!

# F.A.Q. (Instructor Anticipated Questions)

1. Q: The network is not working!
	- A: Try a different ip, try a different port number, perhaps try a different wifi(mobile hotspot instead of Northeastern's netwrok).

