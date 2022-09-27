#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include "splitter.c"


bool state = true;

int execute_command(char **arr1, char **arr2) {

    // Create pipe between two processes

    int pd[2]; // 0 --> read, 1 --> write

    // Check pipe error
    if(arr2 != NULL) {
        int myPipe = pipe(pd);
        if(myPipe == -1) {
            printf("Pipe error");
        }
    }

    pid_t pid = fork();


    // If fork failure
    if(pid < 0) {
        printf("Fork failure");
        exit(1);
    }

    // Open and close read & write
    if (pid == 0) {
        if(arr2 != NULL) {
            close(pd[0]);
            dup2(pd[1], STDOUT_FILENO); // Output of process 1
            close(pd[1]);
        }
        // System call
        execvp(arr1[0], arr1);
    }

    pid_t pid2 = -1;
    if(arr2 != NULL) {
        pid2 = fork();
        if(pid2 < 0) {
            printf("Fork failure");
            exit(1);
        }

        if (pid2 == 0) {
            close(pd[1]);
            dup2(pd[0], STDIN_FILENO); // Input of process 1
            close(pd[0]);
            execvp(arr2[0], arr2);
        }
    }

    if(arr2 != NULL) {
        close(pd[0]);
        close(pd[1]);
        waitpid(pid2, NULL, 0);
    }

    waitpid(pid, NULL, 0);
    return 0;

}


int main() {
    printf("you can use the following commands in this shell: ls, pwd, ping, cd, help and exit\n");
    while(state) {

        // Take input from user
        char input[100];
        printf("> ");
        scanf(" %[^\t\n]s",&input); // Allows for spaces in input

        // Tokenize
        input[strcspn(input, "\n")] = 0;
        char *input1 = strtok(input, "|");
        char *input2 = strtok(NULL, "|");

        // Tokenize input from user to take each keyword as different commands --> arr1[0] = cd --> arr1[1] = SOME DIRECTORY
        char **arr1 = tokenization(input1);
        char **arr2 = NULL;
        if(input2 != NULL) {
            arr2 = tokenization(input2);
        }


        // Commands to be executed
        if(!strcmp(arr1[0], "ls") | !strcmp(arr1[0], "pwd") | !strcmp(arr1[0], "ping")) {
            execute_command(arr1, arr2);
        } else if(!strcmp(arr1[0], "help")) {
            printf("you can use the following commands in this shell: ls, pwd, ping, cd, help and exit\n");
        } else if(strcmp(arr1[0], "exit") == 0) {
            exit(0);
        } else if(!strcmp(arr1[0], "cd")) {
            chdir(arr1[1]); // System call chdir for cd
        } else {
            printf("unknown command: %s\n", arr1[0]);
        }


    }
}

