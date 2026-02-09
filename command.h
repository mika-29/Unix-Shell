#ifndef EXECUTOR_H           
#define EXECUTOR_H          

#include <stdbool.h>        

typedef struct {
    char *command;          // The command name (e.g., "ls")
    char *args[256];        // Arguments array (NULL-terminated)
    char *input_file;       // Filename for < redirection (NULL if none)
    char *output_file;      // Filename for > or >> redirection
    bool append;            // true if >> (append), false if > (overwrite)
    bool background;        // true if & is present
} Command;


Command parse_input(char *input);                   //parses user input into command structure
int execute_command(Command *cmd);                  //executes the parsed command 

#endif