#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "splitter.c"


bool state = true;
char cwd[512];

int execute_command(char **input) {

    pid_t pid = fork();

    // If fork failure
    if(pid < 0) {
        printf("Fork failure");
        exit(1);
    }


    if (pid == 0) {
        execvp(input[0], input);
    }

    waitpid(pid, NULL, 0);
    return 0;


}

int main() {
    //int pid;
    while(state) {

        // Take input from user
        char input[100];
        printf("> ");
        scanf(" %[^\t\n]s",&input); // Allows for spaces in input

        // Tokenize
        input[strcspn(input, "\n")] = 0;
        char **string = tokenization(input);



        if(!strcmp(string[0], "ls") | !strcmp(string[0], "pwd") | !strcmp(string[0], "ping")) {
            execute_command(string);
        } else if(strcmp(string[0], "exit") == 0) {
            exit(0);
        }

        if(!strcmp(string[0], "cd")) {
            chdir(string[1]);
        }

        //pid = fork();

        //Pipe


    }
}

