//This will include all functions in our language

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define BUFFER_SIZE 1024
#define FILE_NOT_FOUND_ERROR "\033[0;31mHATA: ARANAN DOSYA BULUNAMADI\n\033[0m"
#define NO_FUNCTION_ERROR "\033[0;31mHATA: SATIRDA FONKSIYON BULUNAMADI\n\033[0m"
#define CANT_READ_VAR_ERROR "ERROR: CAN'T FIND THE OTHER ';' TO READ VARIABLE"

#define atoa(x) #x

unsigned short lineAmount = 0; //lines amount
int varAmount = 0; //variables that user created amount 

static char varNames[BUFFER_SIZE][BUFFER_SIZE];  //variables that user create
static char varValues[BUFFER_SIZE][BUFFER_SIZE]; //value of them ↑

void CLOSE_APP(char *message, int error){
    printf("\033[0;31m%s\033[0m", message);
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
        printf(FILE_NOT_FOUND_ERROR);
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
        printf(FILE_NOT_FOUND_ERROR);
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
        printf(FILE_NOT_FOUND_ERROR);
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
    free(input);
}

char* replaceWord(const char* s, const char* oldW, const char* newW) { 
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
 
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; (tmp = strstr(ins, rep)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void append_char(char *str, char ch) {
    int len = strlen(str);
    
    str[len] = ch;
    str[len + 1] = '\0'; // Add the null terminator at the new end of the string
}

int comparevar(char *first, char *second){ //strcmp didn't work, so i instead made my own
    int i = 0;
    for(i = 0; i < strlen(first); i++){
        if(first[i] != second[i]){
            return -1;
        }
    }
    return 0;
}

void intToStr(int N, char *str) {
    int i = 0;
  
    int sign = N;

    if (N < 0)
        N = -N;

    while (N > 0) {
        str[i++] = N % 10 + '0';
      	N /= 10;
    } 

    if (sign < 0) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

void remove_char(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

void GET_INPUT(char *varName){
    char *takenInput = malloc(BUFFER_SIZE);
    scanf(" %1024[^\n]", takenInput);

    int i = -1;
    while(i < varAmount - 1){
        i++;
        char *loc = varNames[i];
        
        if(comparevar(loc, varName) == 0){
            strcpy(varValues[i], takenInput);
            break;
        }
    }
    free(takenInput);
}
