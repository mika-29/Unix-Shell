# UNIX SHELL - CMSC 125 [Lab 1]

## Group Members
Borces, Michaela F.
Tambolero, Marinelle Joan U.

## Compilation and Usage Instructions

**To compile:** From inside the project directory, compile with: gcc -Wall -Wextra -o mysh *.c

**To run the shell:** Run with: ./mysh

**List of implemented features:** 
- Built-in commands:
      - cd
      - pwd
      - exit
      - jobs
- Input redirection: <
- Output redirection: > and >>
- Bakground execution: &
- Background jobs that exit immediately
- Array of background jobs with PIDS
- Reaping of finished background jobs
- Multiple concurrent background jobs
- Shell remains responsive while background jobs are still running
- Exterminate background jobs when exiting

**Known limitations and bugs:** 
- The shell doesn't fully support quoted strings with spaces (e.g., echo "hello world"). Quotation marks are treated as literal characters instead of being removed during parsing.
- Doesn't properly handle inputs containing spaces.


**Design decisions and architecture overview:** The shell is organized into the following components:

- command.h - defines the command structure and holds the function declarations.
- main.c - Implements the main shell loop, background job tracking, zombie reaping, and cleanup.
- parser.c - mainly does the parsing of user input into a Command structure, handling arguments, and input redirection.
- executor.c - Execute commands, handle built-in commands, perform I/O redirection, and manage background execution.

Background jobs are tracked using an array of PIDS.

Finished background jobs are periodically reaped using waitpid() with WNOHANG.

On exit, all remaining background jobs are terminated and reaped to prevent orphan processes.

**Proof of functionality:**
- Basic Interaction:
![download](https://github.com/user-attachments/assets/81132c9b-de08-4f5d-8720-3d261cea0f01)


- I/O Redirection:
![download](https://github.com/user-attachments/assets/2e47f5bb-d9e4-4b94-b8b8-3709bd518f97)
![download](https://github.com/user-attachments/assets/6e5afdc2-f42d-414b-b611-5318149a6330)
![download](https://github.com/user-attachments/assets/e826cd0d-f908-41bb-b51b-524ade0ad29f)


- Background Jobs:
![download](https://github.com/user-attachments/assets/bff56004-0022-4b88-837a-c44ee5fa7b5c)
![download](https://github.com/user-attachments/assets/bfeba73f-fa91-43f1-ac86-075ed4069d1e)





