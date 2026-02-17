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

typedef enum {
    STATUS_OK,      // Command executed successfully
    STATUS_EXIT,    // User requested to exit the shell
    STATUS_ERROR,   // An error occurred (optional)
    STATUS_EMPTY    // No command was entered
} Status; 



Command parse_input(char *input);                   //parses user input into command structure
Status execute_command(Command *cmd);                  //executes the parsed command 

#endif