#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void COMPILE(char *compileFile){
    system("cls");
    FILE *file = fopen(compileFile, "r"); 
    if(file == NULL || strcmp(get_filename_ext(compileFile), "h2o") != 0){
        system("cls");
        CLOSE_APP(FILE_NOT_FOUND_ERROR, 1);
    }
    else{
        unsigned short lineAmount = 0; //lines amount
        unsigned short varAmount = 0; //variables that user created amount 

        static char varNames[BUFFER_SIZE][BUFFER_SIZE];  //variables that user create
        static char varValues[BUFFER_SIZE][BUFFER_SIZE]; //value of them ↑

        char currentLine[BUFFER_SIZE]; //array to store entire text of currentLine

        int currentLineChar;
        int currentFuncChar;
        int currentStrChar; //DO NOT REMOVE THIS 

        //####### START COMPILING #######
        while(fgets(currentLine, BUFFER_SIZE, file)){ //gets the entire current line text
            currentLineChar = 0;
            currentFuncChar = 0;
            currentStrChar = 0;

            char currentBuffer;
            currentBuffer = currentLine[currentLineChar]; //current character
            
            lineAmount++; //yes it is correct
            
            char readFunc[20]; //array to store current function
            for(int i = 0; i < 20; i++){
                readFunc[i] = '\0'; //clear readFunc
            }
            readFunc[0] = ' ';

            char readStr[BUFFER_SIZE]; //array to store current string
            for(int j = 0; j < 100; j++){
                readStr[j] = '\0'; //clear readFunc
            }
            readStr[0] = ' ';

            char readFileName[BUFFER_SIZE];
            for(int k = 0; k < 50; k++){
                readFileName[k] = '\0'; //clear readFunc
            }
            readFileName[0] = ' ';

            char readVar[50];
            for(int h = 0; h < 50; h++){
                readVar[h] = '\0';
            }
            readVar[0] = ' ';
            int hn = 0;
            int nh = 1;

            while(currentLine[hn] != ';'){
                hn++;
                if(hn > strlen(currentLine)){break;}
            }

            if(currentLine[hn] == ';' && hn != strlen(currentLine)){
                //start reading var here
                readVar[1] = currentLine[hn];
                hn++;
                while(currentLine[hn] != ';'){
                    nh++;
                    readVar[nh] = currentLine[hn];
                    hn++;
                    if(hn > strlen(currentLine)){break;}
                }
                readVar[nh + 1] = ';';
                //readVar+1 is the text to be replaced
                if(currentLine[hn] == ';'){
                    int z = 0;
                    int correction = 0;
                    //finding the variable in array
                    while(z < varAmount){
                        char temp[BUFFER_SIZE];
                        sprintf(temp, "%c%s%c", ';', varNames[z], ';');

                        if(strcmp(temp, readVar+1) == 0){
                            correction = 1;
                            break;
                        }
                        z++;
                    }    
                    if(correction == 1){
                        char temp[BUFFER_SIZE];
                        sprintf(temp, "%c%s%c", ';', varNames[z], ';');

                        char *res = replaceWord(currentLine, temp, varValues[z]);
                        sprintf(currentLine, "%s", res);
                        free(res);
                    }
                }
            }

            while(currentBuffer == ' '){ //for tabs in the beginning of the line
                currentLineChar++;
                currentBuffer = currentLine[currentLineChar];
            }
                    
            if(currentBuffer != ' '){
                if(currentLineChar > 1){currentLineChar--;} //i mean, it works
                currentBuffer = currentLine[currentLineChar];
                //trying to find a function
                
                while(strcmp(readFunc+1, "yazdir") != 0 && strcmp(readFunc+1, "dosyayaEkle") != 0 && strcmp(readFunc+1, "dosyayaYaz") != 0 && strcmp(readFunc+1, "cikis") != 0 && strcmp(readFunc+1, "hataIleCikis") != 0 && strcmp(readFunc+1, "dosyaOku") != 0 && strcmp(readFunc+1, "satirOku") != 0 && strcmp(readFunc+1, "yeniSatir") != 0 && strcmp(readFunc+1, "girdiAl") != 0 && strcmp(readFunc+1, "yazi") != 0 && strcmp(readFunc+1, "sayi") != 0){ 
                    if(currentLineChar > strlen(currentLine)){break;}
                    //if no function is found until the end of the line, give no function error
                    currentLineChar++;
                    currentFuncChar++;
                    readFunc[currentFuncChar] = currentBuffer;
                    currentBuffer = currentLine[currentLineChar];
                }
                
                if(strcmp(readFunc+1, "yazdir") == 0){ //if the function is log
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                            
                    //run this after the while is executed
                    currentLineChar++;
                    currentFuncChar = 1;
                        
                    currentBuffer = currentLine[currentLineChar];
                    
                    readStr[1] = currentBuffer;
                    readStr[0] = ' ';

                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                            
                        currentFuncChar++;
                        readStr[currentFuncChar] = currentBuffer;
                    }
                    readStr[currentFuncChar] = '\0';
                    
                    CONSOLE_LOG(&readStr[1]);          
                }

                else if(strcmp(readFunc+1, "dosyayaEkle") == 0 || strcmp(readFunc+1, "dosyayaYaz") == 0){
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }

                    currentLineChar++;
                    currentFuncChar = 1;
                    currentBuffer = currentLine[currentLineChar];
                    
                    readFileName[1] = currentBuffer;
                    readFileName[0] = ' ';
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                            
                        currentFuncChar++;
                        readFileName[currentFuncChar] = currentBuffer;
                    }
                    readFileName[currentFuncChar] = '\0';
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    currentFuncChar = 1;
                    
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                    if(currentBuffer == '"'){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                        readStr[currentFuncChar] = currentBuffer;
                        while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                            currentLineChar++;
                            currentFuncChar++;
                            currentBuffer = currentLine[currentLineChar];                            
                            readStr[currentFuncChar] = currentBuffer;
                        }
                        readStr[currentFuncChar] = '\0';
                    }
                    if(strcmp(readFunc+1, "dosyayaEkle") == 0){
                        readStr[0] = '\n';
                        printf("DOSYAYA YAZI EKLEME ISLEMI GERCEKLESTIRILDI\n");
                        WRITE_TO_FILE(readFileName + 1, readStr, "a");
                    }
                    else if(strcmp(readFunc+1, "dosyayaYaz") == 0){
                        printf("DOSYAYA YAZI YAZMA ISLEMI GERCEKLESTIRILDI\n");
                        WRITE_TO_FILE(readFileName + 1, readStr + 1, "w");
                    }
                }

                else if(strcmp(readFunc+1, "cikis") == 0){
                    CLOSE_APP("\n\nUygulamadan cikiliyor...", 0);
                }

                else if(strcmp(readFunc+1, "hataIleCikis") == 0){
                    //todo this
                }

                else if(strcmp(readFunc+1, "dosyaOku") == 0){
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }

                    currentLineChar++;
                    currentFuncChar = 1;
                    currentBuffer = currentLine[currentLineChar];
                    
                    readFileName[1] = currentBuffer;
                    readFileName[0] = ' ';
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                            
                        currentFuncChar++;
                        readFileName[currentFuncChar] = currentBuffer;
                    }
                    readFileName[currentFuncChar] = '\0';
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    currentFuncChar = 1;

                    READ_ENTIRE_FILE(readFileName + 1);
                }

                else if(strcmp(readFunc+1, "satirOku") == 0){
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }

                    currentLineChar++;
                    currentFuncChar = 1;
                    currentBuffer = currentLine[currentLineChar];
                    
                    readFileName[1] = currentBuffer;
                    readFileName[0] = ' ';
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                            
                        currentFuncChar++;
                        readFileName[currentFuncChar] = currentBuffer;
                    }
                    readFileName[currentFuncChar] = '\0';
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    currentFuncChar = 1;
                    
                    while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                    if(currentBuffer == '"'){
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                        readStr[currentFuncChar] = currentBuffer;
                        while(currentBuffer != '"' && currentLineChar < sizeof(currentLine)){
                            currentLineChar++;
                            currentFuncChar++;
                            currentBuffer = currentLine[currentLineChar];                            
                            readStr[currentFuncChar] = currentBuffer;
                        }
                        readStr[currentFuncChar] = '\0';
                    }
                    READ_SPECIFIC_LINE(readFileName + 1, atoi(readStr + 1));
                }

                else if(strcmp(readFunc+1, "yeniSatir") == 0){
                    printf("\n");
                }

                else if(strcmp(readFunc+1, "girdiAl") == 0){
                    
                }

                else if(strcmp(readFunc+1, "sayi") == 0 || strcmp(readFunc+1, "yazi") == 0){
                    while(currentBuffer == ' '){
                        if(currentLineChar > strlen(currentLine)){break;}
                        //if no function is found until the end of the line, give no function error
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                    if(currentBuffer != ' '){
                        currentFuncChar = 0;

                        currentStrChar++;
                        readStr[currentStrChar] = currentBuffer;
                        
                        while(currentBuffer != ' '){
                            currentLineChar++;
                            currentStrChar++;
                            currentBuffer = currentLine[currentLineChar];
                            readStr[currentStrChar] = currentBuffer;
                        }
                        readStr[currentStrChar] = '\0';
                        //now readStr is the variable name

                        currentStrChar++;
                        currentBuffer = currentLine[currentLineChar];
                        while(currentBuffer != '"'){
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }
                        if(currentBuffer == '"'){
                            currentLineChar++;
                            currentFuncChar++;
                            currentBuffer = currentLine[currentLineChar];
                            readFileName[0] = ' ';
                            readFileName[1] = currentBuffer;
                            while(currentBuffer != '"'){
                                currentLineChar++;
                                currentFuncChar++;
                                currentBuffer = currentLine[currentLineChar];
                                readFileName[currentFuncChar] = currentBuffer;
                            }
                            if(currentBuffer == '"'){ //now we got both name and value
                                readFileName[currentFuncChar] = '\0';
                                
                                strcpy(varNames[varAmount], readStr+1);
                                strcpy(varValues[varAmount], readFileName+1);
                                //add new variable to array
                                
                                varAmount++;
                            }
                        }
                    }
                }
            }
        }
    }   
    free(file);
    free(compileFile);
}