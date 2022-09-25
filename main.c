#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>


bool state = true;
char cwd[512];

void execute_command(char input[]) {

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

    //

    if(!strcmp(input, input)) {
        execlp(input, input, NULL);
    } else {
        printf("command not found: %s\n", input);
    }

}

int main() {
    int pid;
    while(state) {
        char input[100];
        printf("> ");
        //scanf("%s", input);
        scanf(" %[^\t\n]s",&input);
        input[strcspn(input, "\n")] = 0;
        //char *string = tokenization(input);

        pid = fork();

        if(pid < 0) {
            printf("Fork failure");
            exit(1);
        }

        // Kill parent process and all child processes
        if(!strcmp(input, "exit")) {
            kill(-1*pid, SIGKILL);
        }

        if (pid == 0) {
            execute_command(input);
        }

        waitpid(pid, NULL, 0);
    }
}
