# UNIX SHELL

## Problem Analysis 
The goal of this laboratory is to implement a UNIX SHELL using POSIX API. The shell must interpret user commands, 
execute programs, and manage processes while remaining interactive. 

**Key challenges include:** 

**Process Management:** External commands must be executed using the fork-exec model so the shell continues running after each command. 

**Process Synchronization:** The shell must support both foreground execution, where it waits for the process to finish, and background execution using the & operator, while preventing zombie processes.

**Input/Output Redirection:** The shell must support <, >, >> by redirecting standard input and output using file descriptors.

**Command Parsing:** The shell must distinguish between built-in and external commands and must know how to handle invalid input. 

## Solution Architecture 
The shell follows a **Read-Evaluate-Print Loop (REPL)** design. 

**>>Initialization**

The shell initializes required data structures and sets up signal handling so interrupts do not terminate the shell itself. 

**>>Command Processing** 

Each command follows this pipeline: 

**Read:** Accept user input using fgets(). 

**Parse:** Tokenize the input using strtok() to exctract the command, arguments, redirection operators, and background execution flag. 

**Execute:** 

      >Built-in commands are executed directly in the parent process. 
      
      >External Commands are executed by forking a child process. The child applies I/O redirection using open() and dup2() before calling execvp().

      >The parent process waits for foreground commands using waitpid(). For background commands, it immediately returns to the prompt and periodically reaps finished processes using waitpid() with WNOHANG.
      
**>>Termination** 
The shell exits on the exit command or EOF, performing cleanup and ensuring all child processes are properly handled. 

