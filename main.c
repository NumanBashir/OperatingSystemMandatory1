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
    } else if(strcmp(input[0],"exit") == 0) {

    waitpid(pid, NULL, 0);
    return 0;


    //printf("%s", input);
    /*if(!strcmp(input, "ls")) {
        execlp(input, "-a", NULL);
    } else if(!strcmp(input, "exit")) {
        printf("Program exited");
    } else if(!strcmp(input, "pwd")) {
        execlp("pwd", "pwd", NULL);
        printf("%s\n", cwd);
    } else if(!strcmp(input, "cd")) {
        printf("please enter argument\n");
    } else if(!strcmp(input, "cd ..")) {
        chdir("..");
    } else if(!strcmp(input, "ping")) {
        execlp("ping", "ping", "google.dk", NULL);
    } else {
        printf("command not found: %s\n", input);
    }*/

    //test

    /*if(!strcmp(input, input)) {
        execlp(input, input, NULL);
    } else {
        printf("command not found: %s\n", input);
    }*/

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

    }

        //pid = fork();


    }
}

