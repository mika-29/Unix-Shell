#include <string.h>
#include "command.h"

Command parse_input(char *input) {
    Command cmd;
    char *token;
    int i = 0; 

    token = strtok(input, " ");
    while (token != NULL && i < 255){
        cmd.args[i++] = token;
        token = strtok(NULL, " ");
    }
    cmd.args[i] = NULL; // Null-terminate the args array
    return cmd;
} 