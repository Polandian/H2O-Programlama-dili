#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char varNames[256][256];  //variables that user create
char varValues[256][256]; //value of  them ↑

char functionNames[256][256];      //Name of user created functions
char functionParameters[256][256]; //Parameters of those
char functionVoid[256][256];       //The code to be ran in functions

int readMode = 0; //0 = compile normally 
                  //1 = read function 
                  //2 = if/else statement is wrong, so go until bitir
int funcReading = 0;

#include "include/h2oFunctions.h"
#include "include/compile.h"

int main(){
    /*char *testChar = "Hello World"; //Define a string
    printf("%c", *testChar); //get the first character of string
    printf("%c", *(testChar + 1)); //get the second character of string
    printf("%d", strlen(testChar)); //gets the length of the string (without \0)
    free(testChar); //frees memory */

    //TODO BUILT-IN KULLAN FUNCTIONS
    //TODO ERROR MESSAGES

    system("cls"); //clears screen

    char *fs = malloc(BUFFER_SIZE); //file to run
    
    printf("Calistirilacak dosyayi girin: ");
    scanf("%1024[^\n]", fs);

    system("cls");
    COMPILE(fs, 0); //compiles the file here
    free(fs);    //free file name here

    char canExit[BUFFER_SIZE];
    printf("\n\n\n\n\n\e[44mKod calistirildi, artik bu pencereyi kapatabilirsiniz...\033[0m\e[0m");
    scanf("%s", canExit);
    return 0;
}
