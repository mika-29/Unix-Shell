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
- executor.c - Execute commands, handles built-in commands, performs I/O redirection, and manages background execution.

Background jobs are trackes using an array of PIDS.
Finished background jobs are periodically reaped using waitpid() with WNOHANG.
On exit, all remaining background jobs are terminated and reaped to prevent orphan processes.

**Proof of functionality:**
- Basic Interaction:
![basic interaction](image.png)

- I/O Redirection:
![I/O 1](image-1.png)
![I/O 2](image-2.png)
![I/O 3](image-3.png)

- Background Jobs:
![bg jobs 1](image-4.png)
![bg jobs 2](image-5.png)




