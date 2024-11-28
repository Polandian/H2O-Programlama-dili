//Today, we are going to make a simple programming language
//Written in C
//In which we MAYBE can update later on if i decide the base code in good enough
//Because h2o is already a project, i just dont have enough C knowledge to start doing it

//Functions we are going to cover this time:
/*
-creating own functions (somehow idk how but somehow)
-calculations somehow with a while loop to looks for the new char that is a operator
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


    //TODO HATAİLEÇIKIŞ
    //TODO ERROR MESSAGES
    //TODO BE ABLE TO USE FUNCTIONS BY CALLING THEIR NAME WITH () PARANTHESES

    //TODO https://stackoverflow.com/a/55473328/28041550 FOR USER FUNCTIONS

    system("cls"); //clears screen
    
    char *fs = malloc(BUFFER_SIZE); //file to run
    
    /*char *userDedicate = malloc(1024);
    USER_INPUT(userDedicate);
    free(userDedicate);*/

    printf("Calistirilacak dosyayi girin: ");
    scanf("%1024[^\n]", fs);

    system("cls");
    COMPILE(fs); //compiles the file here
    free(fs);    //free file name here

    char canExit[BUFFER_SIZE];
    printf("\n\n\n\n\n\e[44mKod calistirildi, artik bu pencereyi kapatabilirsiniz...\033[0m\e[0m");
    scanf("%s", canExit);
    return 0;
}
