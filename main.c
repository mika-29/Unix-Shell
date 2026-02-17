#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/wait.h>
#include "command.h"

void free_command_content(Command *cmd);

int main(){
    char input[1024];

    while(1){

        int status;
        pid_t pid;
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0){
            printf("Background process %d finished with status %d\n", pid, WEXITSTATUS(status));
        }                                                                // Reap any finished background processes
        
        printf("mysh> ");
        if(fgets(input, sizeof(input), stdin) == NULL){
            break;                                                       // EOF or error
        }

        input[strcspn(input, "\n")] = 0;                                // Remove newline
        
        while (input[0] == ' ' || input[0] == '\t') {
            memmove(input, input + 1, strlen(input) + 1);               // Trim leading whitespace
        }

        if (strlen(input) == 0) {
            continue;                                                   // Skip empty input
        }
        
        Command cmd = parse_input(input);
        
        Status result = execute_command(&cmd);

        if (result == STATUS_EXIT) {
            free_command_content(&cmd);
            printf("Exiting mysh...\n");
            break;                                                       // Exit the shell loop
        }

        free_command_content(&cmd); 
    }

    return 0;
}

void free_command_content(Command *cmd) {
    for (int j = 0; cmd->args[j] != NULL; j++) {
        free(cmd->args[j]);
        cmd->args[j] = NULL; 
    }
    if (cmd->input_file) {
        free(cmd->input_file);
        cmd->input_file = NULL;
    }
    if (cmd->output_file) {
        free(cmd->output_file);
        cmd->output_file = NULL;
    }
}