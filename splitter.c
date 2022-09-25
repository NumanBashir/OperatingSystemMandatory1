/*============================================================================
 Name        : 029 strtok
 Author      : Declined#8151 (Discord ID), s090116
 Version     : 1.00
 Date        : 08/09-2022
 Copyright   : Your copyright notice
 Description : A program to to create a strtok function, that returns a double
               pointer to the tokenized string.
               This code can be altered to be handled in 3 different methods
               for getting a double pointer with the content
               Method A: Supply address of double pointer as an argument
               Method B: Use return value of the function
               Method C: Store in Global pointer
 ============================================================================*/

#include <string.h>
#include <stdlib.h>


/**
 * @brief Tokenizing a string,
 * currently supports 3 methods of presenting
 * the tokenized double char pointer.
 */
char **tokenization(char input[]){
    int count = 0;
    char **carbon_copy;
    char *stringtobesplit = malloc(sizeof(char)*strlen(input));
    char *usedforcount;

// Part 1, find out how many strings will be needed.
    strcpy(stringtobesplit, input);                   // Temporarily store the word
    usedforcount = strtok(stringtobesplit, " ");      // First word
    while( usedforcount != NULL ) {                   // Used to figure out how many words are in the string
        usedforcount = strtok(NULL, " ");               // The addtional words in the string is tokenized by whitespace
        count++;
    }

// Part 2, Initializing space for the double pointers.
    carbon_copy = malloc(sizeof(char *) * (count + 1));
    for(int i = 0; i <= count; i++){
        carbon_copy[i] = NULL;
    }

// Part 3, tokenization
    strcpy(stringtobesplit, input);               // copies the original userInput string into stringtobesplit

    //tokenizing the string
    for(int i = 0; i < count; i++){
        if(i == 0)
            usedforcount = strtok(stringtobesplit, " ");
        else
            usedforcount = strtok(NULL, " ");
        carbon_copy[i] = strdup(usedforcount);
    }

// Part 4, organizing return values and cleaning up memory
    free(stringtobesplit);

    return carbon_copy;                 // Method C, utilizing the return value of the function
}

