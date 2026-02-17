#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <fcntl.h>
#include "command.h"

Status execute_command(Command *cmd) {
    static int global_job_id = 1;
    if (cmd->command == NULL) {
        return STATUS_EMPTY;                                                   // No command entered
    }

    if (strcmp(cmd->command, "exit") == 0) {
            return STATUS_EXIT;                           
        }

    if (strcmp(cmd->command, "cd") == 0) {
        if (cmd->args[1] == NULL) {
            fprintf(stderr, "mysh: expected argument to \"cd\"\n");
        } else {
            if (chdir(cmd->args[1]) != 0) {
                perror("mysh");
                return STATUS_ERROR;                                               // Handle 'cd' error
            }
        }
        return STATUS_OK;                                                   // Handle built-in 'cd' and skip to next loop
    }

    if(strcmp(cmd->command, "pwd") == 0){
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        } else {
            perror("mysh");
            return STATUS_ERROR;                                               // Handle 'pwd' error
        }
        return STATUS_OK;                                                   // Handle built-in 'pwd' and skip to next loop
    }

    pid_t pid = fork();                                            // External Command Execution

    if (pid == 0) {

        if (cmd->input_file != NULL) {
            int fd_in = open(cmd->input_file, O_RDONLY);
            if (fd_in < 0) {
                perror("open input file error");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (cmd->output_file != NULL) {
            int flags = O_WRONLY | O_CREAT;
            if (cmd->append) {
                flags |= O_APPEND; 
            } else {
                flags |= O_TRUNC; 
            }
            int fd_out = open(cmd->output_file, flags, 0644);
            if (fd_out < 0){
                perror("open output file error");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
            
        if (execvp(cmd->args[0], cmd->args) == -1) {                       // execvp takes the command name and the entire args array
            fprintf(stderr, "mysh: command not found: %s\n", cmd->args[0]);
            perror("exec failed");
            exit(EXIT_FAILURE);                                              // Exit child if execvp fails
        }                                        // Exit child if execvp fails
    } 

    else if (pid < 0) {
        perror("mysh: fork error");    
        return STATUS_ERROR;                                           // Failed Fork 
    } 

    else {
        // Parent process
        if (!cmd->background) {
            int status;
            waitpid(pid, &status, 0);   
            if (WIFEXITED(status)){
                int exit_code = WEXITSTATUS(status);
                if (exit_code != 0){
                    printf("mysh: command exited with code %d\n", exit_code);
                }
            }                                    
        } else {
            // Start the line
            printf("[%d] Started: ", global_job_id++); 
        
        // Print all arguments on the SAME line
            for (int j = 0; cmd->args[j] != NULL; j++) {
                printf("%s ", cmd->args[j]);
            }
        
        // Finalize the line with PID and the crucial newline
            printf("(PID: %d)\n", pid);
        }
    }

    return STATUS_OK;
}