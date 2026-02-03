#ifndef COMMAND_H           
#define COMMAND_H          

#include <stdbool.h>        

typedef struct {
    char *command;          // The command name (e.g., "ls")
    char *args[256];        // Arguments array (NULL-terminated)
    char *input_file;       // Filename for < redirection (NULL if none)
    char *output_file;      // Filename for > or >> redirection
    bool append;            // true if >> (append), false if > (overwrite)
    bool background;        // true if & is present
} Command;

void parse_command(char *input, Command *cmd);      //parses user input into command structure

void execute_command(Command *cmd);                 //executes the command based on the command structure

void check_background_jobs();                       //here to solve the zombie problem

#endif