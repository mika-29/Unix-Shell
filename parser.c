#include <string.h> 
#include <stdlib.h>
#include <stdbool.h> 
#include "command.h"

Command parse_input(char *input) {
    Command cmd;                                        
    cmd.input_file = NULL;                  //prevent program from reading garbage data 
    cmd.output_file = NULL;
    cmd.append = false;
    cmd.background = false;

    char *token = strtok(input, " ");
    int i = 0; 

    while (token != NULL && i < 255){
        size_t len = strlen(token);
        if(len >= 2 && token[0] == '"' && token[len - 1] == '"'){
            token[len - 1] = '\0';          // Remove trailing quote
            token++;                        // Remove leading quote
        }

        if (strcmp(token, ">") == 0) {        // Input redirection
            token = strtok(NULL, " \t");
            if (token) cmd.output_file = strdup(token);
            cmd.append = false;
        } 
        else if (strcmp(token, ">>") == 0) {
            token = strtok(NULL, " \t");
            if (token) cmd.output_file = strdup(token);
            cmd.append = true;
        } 
        else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t");
            if (token) cmd.input_file = strdup(token);
        } 
        else if (strcmp(token, "&") == 0) {
            cmd.background = true;
        } 
        else {
            cmd.args[i++] = strdup(token);      //It's a regular argument/command
        }

        token = strtok(NULL, " \t");
    }

    cmd.args[i] = NULL;                     // Null-terminate the args array

    if(i > 0){
        cmd.command = cmd.args[0];          // First token is the command
        } else {
            cmd.command = NULL;                 // No command entered
        }
    return cmd;
} 
 