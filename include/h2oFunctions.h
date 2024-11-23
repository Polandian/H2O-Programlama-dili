//This will include all functions in our language

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define FILE_NOT_FOUND_ERROR "ERROR: WANTED FILE CAN NOT BE FOUND"
#define NO_FUNCTION_ERROR "ERROR: CAN'T FIND A FUNCTION IN LINE"

void CLOSE_APP(char *message, int error){
    printf("%s", message);
    if(error == 0){ //if not error
        exit(0);
    }
    else if(error == 1){ //if error
        abort();
    }
    free(message);
}

void CONSOLE_LOG(char *log){ //Enters a text to the console
    printf("%s\n", log);
    free(log);
}

void READ_ENTIRE_FILE(char *fileName){ //Gets a file and reads the entire text of it
    FILE *fileToBeRead = fopen(fileName, "r"); //Open file
    if(fileToBeRead == NULL){ //If file not found
        system("cls");
        CLOSE_APP(FILE_NOT_FOUND_ERROR, 1);
    }
    else{ //If it does exist read the file
        char fileText[BUFFER_SIZE] = "\0";
        char currentLine[BUFFER_SIZE];
        while(fgets(currentLine, BUFFER_SIZE, fileToBeRead)) {
            strcat(fileText, currentLine);
        }
        printf("\n%s: '%s'\n", fileName, fileText);
    }
    fclose(fileToBeRead); //Free memory
    free(fileName);
    free(fileToBeRead);
}

void READ_SPECIFIC_LINE(char *fileName, int line){
    FILE *fileToBeRead = fopen(fileName, "r");
    char rdl[1024];
    int count = 0;
    line--; //make it 1 less so that you can properly read it
    if(fileToBeRead == NULL){
        system("cls");
        CLOSE_APP(FILE_NOT_FOUND_ERROR, 1);
    }
    else{
        while(fgets(rdl, BUFFER_SIZE, fileToBeRead) != NULL){
            if(count == line){
                printf("%s", rdl);
                break;
            }
            else{
                count++;
            }
        }
    }
    fclose(fileToBeRead);
}

void WRITE_TO_FILE(char *fileName, char *textToWrite, char *writeType){
    //a with a \n at the beginning to append (add in new text without overwriting the file)
    //w to overwrite entire file with new text

    FILE *fileToOverwrite = fopen(fileName, writeType);

    if(fileToOverwrite == NULL){
        system("cls");
        CLOSE_APP(FILE_NOT_FOUND_ERROR, 1);
    }
    else{
        fprintf(fileToOverwrite, textToWrite); //prints the text
    }

    fclose(fileToOverwrite); //Free memory
    free(fileName);
    free(textToWrite);
}

int NUMBER_CALCULATION(float number1, float number2, char *operator){
    switch(*operator){
        case '+': return number1 + number2;
        case '-': return number1 - number2;
        case '*': return number1 * number2;
        case 'x': return number1 * number2;
        case '/': return number1 / number2;
        case '%': return fmodf(number1, number2);
        default: ;
    }
    //if didn't get any return value from the switch case
    if(operator == "**"){
        return pow(number1, number2);
    }
    else if(operator == "++"){
        return number1++;
    }
    else if(operator == "--"){
        return number1--;
    }
    else if(operator == "squareRoot" || operator == "√"){
        return sqrt(number1);
    }
    free(operator);
}

const char *USER_INPUT(char *input){
    scanf("%s", &input);
    return input;
}

char* replaceWord(const char* s, const char* oldW, 
                const char* newW) 
{ 
    char* result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
 
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) { 
        if (strstr(&s[i], oldW) == &s[i]) { 
            cnt++; 
 
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
 
    // Making new string of enough length 
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1); 
 
    i = 0; 
    while (*s) { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
 
    result[i] = '\0'; 
    return result; 
} 

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}