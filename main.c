#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 
#include "command.h"

int main(){
    char input[1024];

    while(1){
        printf("mysh> ");
        if(fgets(input, sizeof(input), stdin) == NULL){
            break;                                                       // EOF or error
        }

        input[strcspn(input, "\n")] = 0;                                // Remove newline

        if (strlen(input) == 0) {
            continue;                                                   // Skip empty input
        }
        
        Command cmd = parse_input(input);

        if (strcmp(cmd.command, "exit") == 0) {
            break;                            
        }

        if (strcmp(cmd.command, "cd") == 0) {
            if (cmd.args[1] == NULL) {
                fprintf(stderr, "mysh: expected argument to \"cd\"\n");
            } else {
                if (chdir(cmd.args[1]) != 0) {
                    perror("mysh");
                }
            }
            continue;                                                   // Handle built-in 'cd' and skip to next loop
        }

        if(strcmp(cmd.command, "pwd") == 0){
            char cwd[1024];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            } else {
                perror("mysh");
            }
            continue;                                                   // Handle built-in 'pwd' and skip to next loop
        }
        
    pid_t pid = fork();                                                 // External Command Execution

    if (pid == 0) {
        // Child
        if (execvp(cmd.args[0], cmd.args) == -1) {                       // execvp takes the command name and the entire args array
            fprintf(stderr, "mysh: command not found: %s\n", cmd.args[0]);
        }
        exit(EXIT_FAILURE);                                              // Exit child if execvp fails
    } 
    else if (pid < 0) {
        perror("mysh fork error");                                      // Failed Fork 
    } 
    else {
        // Parent
        int status;
        waitpid(pid, &status, 0);                                       // Wait for the child to finish
    }
    }
    return 0; 
}