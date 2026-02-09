#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "command.h"

int main(){
    char input[1024];

    while(1){
        printf("mysh> ");
        if(fgets(input, sizeof(input), stdin) == NULL){
            break; // EOF or error
        }
        if(strcmp(input, "exit\n") == 0){
            break; // EOF or error
        }

        input[strcspn(input, "\n")] = 0; // Remove newline

        if (strlen(input) == 0) {
            continue; // Skip empty input
        }
        //Command cmd = parse_input(input);

        //if (strcmp(cmd.args[0], "exit") == 0) {
            //break; // Exit the shell
        //}
    }
    return 0; 
}