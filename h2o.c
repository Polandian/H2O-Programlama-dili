#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char varNames[256][256];  //variables that user create
char varValues[256][256]; //value of  them ↑

char functionNames[256][256];      //Name of user created functions
char functionParameters[256][256]; //Parameters of those
char functionVoid[256][256];       //The code to be ran in functions

int readMode = 0; //0 = compile normally 1 = read function 2 = read if/else statement

#include "include/h2oFunctions.h"
#include "include/compile.h"

int main(){
    /*char *testChar = "Hello World"; //Define a string
    printf("%c", *testChar); //get the first character of string
    printf("%c", *(testChar + 1)); //get the second character of string
    printf("%d", strlen(testChar)); //gets the length of the string (without \0)
    free(testChar); //frees memory */

    //TODO ERROR MESSAGES

    //TODO PASSING VALUES TO THE TEMPORARY FILES CREATED
    //AND RUN THEM VIA kullan
    //FUNCTIONS TO SEPERATE VARIABLES AND CREATE FILE+WRITE TO THEM ARE IN THE BEGINNING OF h2oFunctions.h
    
    //TODO FOR USER FUNCTIONS, JUST KEEP READING AND ADD ALL THE LINES UNTIL bitir TO A STRING, AND WHEN CALLED JUST RUN IT FROM THE STRING ARRAY
    //EXAMPLE:
    /*
    fonksiyon yazma(yazi){
        yazdir "&yazi&"
    }

    THIS ↑ IS A FUNCTION
    
    IMO, WE CAN CREATE A TEMPORARY FILE
    RUN IT
    AND THEN REMOVE IT WITH remove("filename.h2o");
    yeah this seems smart

    TODO also make some in-built functions to assign a value from a file to a string and etc
    */

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
