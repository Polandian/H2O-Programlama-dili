//Today, we are going to make a simple programming language
//Written in C
//In which we MAYBE can update later on if i decide the base code in good enough
//Because h2o is already a project, i just dont have enough C knowledge to start doing it

//Functions we are going to cover this time:
/*
-print
-all file actions (w, r)
-creating own functions (somehow idk how but somehow)
-data types (int, char (also string), bool)
-closing the app when finished (in the programming language ofc) via exit(int)
-calculations somehow with a while loop to looks for the new char that is a operator
-also maybe inputs but probably not today
*/

//By the way im a pretty beginner in C
//Like i made total of 1 projects in this language and i know absolutely nothing about it
//So like pls dont call me a dumbass plz ty

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/h2oFunctions.h"
#include "include/compile.h"

int main(){
    /*char *testChar = "Hello World"; //Define a string
    printf("%c", *testChar); //get the first character of string
    printf("%c", *(testChar + 1)); //get the second character of string
    printf("%d", strlen(testChar)); //gets the length of the string (without \0)
    free(testChar); //frees memory */

    //free memory
    /*for (int i = 0; i < 5; i++) {
        free(my_strings[i]);
    }
    */
    //btw to detect if a variable is a number or not
    //just do atoi on it
    //if its a string it will always give 0
    //and also check if its own value equals to '0'


    //TODO HATAİLEÇIKIŞ
    //TODO MULTIPLE FILES (HEADERS)
    //TODO MATH (EASIEST IMO)
    
    //TODO https://stackoverflow.com/a/55473328/28041550 FOR USER FUNCTIONS

    
    system("cls"); //clears screen
    
    char *fs = malloc(1024); //file to run
    
    /*char *userDedicate = malloc(1024);
    USER_INPUT(userDedicate);
    free(userDedicate);*/

    printf("Calistirilacak dosyayi girin: ");
    scanf("%s", fs);

    COMPILE(fs); //compiles the file here
    free(fs);    //free file name here

    char canExit[1024];
    printf("\n\n\n\n\nKod calistirildi, artik bu pencereyi kapatabilirsiniz...");
    scanf("%s", canExit);
    return 0;
}