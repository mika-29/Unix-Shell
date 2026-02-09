#include <stdio.h>
#include <string.h>
#include "command.h"

int main(){
    char input[1024];

    while(1){
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
        
        if (execute_command(&cmd)) {
            break;                                                      // Exit if 'exit' command is executed
        }
    }

    return 0;
}