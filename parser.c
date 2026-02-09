#include <string.h>
#include "command.h"

Command parse_input(char *input) {
    Command cmd;
    cmd.input_file = NULL;
    cmd.output_file = NULL;
    cmd.append = false;
    cmd.background = false;

    char *token = strtok(input, " ");
    int i = 0; 

    while (token != NULL && i < 255){
        cmd.args[i++] = token;
        token = strtok(NULL, " ");
    }
    cmd.args[i] = NULL;                     // Null-terminate the args array

    if(i > 0){
        cmd.command = cmd.args[0];          // First token is the command
    } else {
        cmd.command = NULL;                 // No command entered
    }

    return cmd;
} 