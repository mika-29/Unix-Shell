#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/wait.h>
#include <signal.h>
#include "command.h"

#define MAX_BG 100 

pid_t bg_pids[MAX_BG];
int bg_count = 0;

int main(){
    char input[1024];

    while(1){

        cleanup_background_processes();                                  // Reap any finished background processes
        
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
            cleanup_on_exit();                                                   // Clean up background processes before exiting
            free_command_content(&cmd);
            printf("Exiting mysh...\n");
            break;                                                       // Exit the shell loop
        }

        free_command_content(&cmd); 
    }

    return 0;
}

void cleanup_background_processes(void) {
    int status;

    for (int i = 0; i < bg_count; i++) {
        pid_t result = waitpid(bg_pids[i], &status, WNOHANG);

        if (result > 0) {
            if (WIFEXITED(status)) {
                printf("Background process %d finished with exit code %d\n",
                       bg_pids[i], WEXITSTATUS(status));
            }
            for (int j = i; j < bg_count - 1; j++) {
                bg_pids[j] = bg_pids[j + 1];
            }
            bg_count--;
            i--;  
        }
    }
}

void cleanup_on_exit(void) {
    int status;

    for (int i = 0; i < bg_count; i++) {
        kill(bg_pids[i], SIGTERM);
    }
    
    for (int i = 0; i < bg_count; i++) {
        waitpid(bg_pids[i], &status, 0);
    }

    bg_count = 0;
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