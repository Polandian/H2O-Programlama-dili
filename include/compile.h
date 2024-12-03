#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void COMPILE(char *compileFile){
    FILE *file = fopen(compileFile, "r"); 
    if(file == NULL || strcmp(get_filename_ext(compileFile), "h2o") != 0){
        system("cls");
        CLOSE_APP(FILE_NOT_FOUND_ERROR, 1);
    }
    else{
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

            char readStr[BUFFER_SIZE];
            for(int j = 0; j < 100; j++){
                readStr[j] = '\0'; //clear readFunc
            }
            readStr[0] = ' ';

            char readFileName[BUFFER_SIZE];
            for(int k = 0; k < 50; k++){
                readFileName[k] = '\0'; //clear readFunc
            }
            readFileName[0] = ' ';

            int b = 0;
            int s = 0;
            int k = 0; /*değer okuyucu*/
            for(; b < strlen(currentLine); b++){
                if(currentLine[b] == ';'){
                    s++;
                }
            }
            while(k < s/2){
                k++;
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
            }
            currentLineChar = 0;
            currentBuffer = currentLine[currentLineChar];

            int bb = 0;
            int ss = 0;
            int kk = 0; /*mathematic*/
            for(; bb < strlen(currentLine); bb++){ //gets all math operators
                if(currentLine[bb] == '+' || 
                currentLine[bb] == '-' || 
                currentLine[bb] == '*' || 
                currentLine[bb] == '/' || 
                currentLine[bb] == '%'){
                    ss++;
                }
            }
            while(kk < ss){
                kk++;
                
                int fn = 0; //first number
                int sn = 0; //second number

                char *fnc = malloc(512); //first number as text
                char *snc = malloc(512); //second number as text
                char *ttr = malloc(512); //text to replace
                char operator;            //operator as char

                fnc[0] = ' ';
                snc[0] = ' ';
                ttr[0] = ' ';

                if(strlen(fnc) > 1){
                    fnc[1] = '\0';
                    fnc[2] = '\0';
                }

                while(currentBuffer != '+' && currentBuffer != '-' && currentBuffer != '*' && currentBuffer != '/' && currentBuffer != '%'){
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];    
                }

                //gets the math operator
                if(currentBuffer == '+' || currentBuffer == '-' || currentBuffer == '*' || currentBuffer == '/' || currentBuffer == '%'){
                    currentLineChar--;
                    currentBuffer = currentLine[currentLineChar];    
                    while(currentBuffer == ' '){ //goes back until there is no space
                        if(currentLineChar < 1){break;}
                        currentLineChar--;
                        currentBuffer = currentLine[currentLineChar];
                    }

                    if(currentBuffer != ' '){ //goes back until there is space
                        while(currentBuffer != ' '){
                            if(currentLineChar < 1){break;}
                            currentLineChar--;
                            currentBuffer = currentLine[currentLineChar];    
                        }
                    }
                    //start reading first number
                    if(currentBuffer == ' ' || currentLineChar == 0){
                        if(currentBuffer == ' '){
                            currentLineChar+=2;
                            currentBuffer = currentLine[currentLineChar];
                        }
                        while(currentBuffer != ' ' && currentBuffer != '+' && currentBuffer != '-' && currentBuffer != '*' && currentBuffer != '/' && currentBuffer != '%' && currentBuffer != '"'){
                            if(currentLineChar > strlen(currentLine) - 1){break;}
                            append_char(fnc, currentBuffer);
                            append_char(ttr, currentBuffer);
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar]; 
                        }
                        append_char(ttr, currentBuffer);
                    }
                    while(currentBuffer == ' '){
                        if(currentLineChar > strlen(currentLine) - 1){break;}
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                        append_char(ttr, currentBuffer);
                    }

                    operator = currentBuffer; //set operator

                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];

                    while(currentBuffer == ' '){
                        append_char(ttr, currentBuffer);
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }

                    while(currentBuffer != ' ' && currentBuffer != '"'){
                        if(currentLineChar > strlen(currentLine) - 1){break;}
                        append_char(snc, currentBuffer);
                        append_char(ttr, currentBuffer);
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar]; 
                    }
                }
                char result[BUFFER_SIZE];
                intToStr(NUMBER_CALCULATION(atoi(fnc+1), atoi(snc+1), &operator), result);
                char *res = str_replace(currentLine, ttr+1, result);

                sprintf(currentLine, "%s", res);
                free(res);
                free(fnc);
                free(snc);
                free(ttr);
            }
            currentLineChar = 0;
            currentBuffer = currentLine[currentLineChar];
        
            while(currentBuffer == ' '){ //for tabs in the beginning of the line
                currentLineChar++;
                currentBuffer = currentLine[currentLineChar];
            }
                    
            if(currentBuffer != ' '){
                if(currentLineChar > 1){currentLineChar--;} //i mean, it works
                currentBuffer = currentLine[currentLineChar];
                //trying to find a function
                
                while(strcmp(readFunc+1, "yazdir") != 0 && strcmp(readFunc+1, "dosyayaEkle") != 0 && strcmp(readFunc+1, "dosyayaYaz") != 0 && strcmp(readFunc+1, "cikis") != 0 && strcmp(readFunc+1, "hataIleCikis") && strcmp(readFunc+1, ":q") != 0 && strcmp(readFunc+1, "dosyaOku") != 0 && strcmp(readFunc+1, "satirOku") != 0 && strcmp(readFunc+1, "yeniSatir") != 0 && strcmp(readFunc+1, "girdiAl") != 0 && strcmp(readFunc+1, "deger") != 0 && strcmp(readFunc+1, "ekle") != 0){ 
                    if(currentLineChar > strlen(currentLine)){break;}
                    //if no function is found until the end of the line, give no function error
                    currentLineChar++;
                    currentFuncChar++;
                    readFunc[currentFuncChar] = currentBuffer;
                    currentBuffer = currentLine[currentLineChar];
                }
                
                if(strcmp(readFunc+1, "yazdir") == 0){
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

                else if(strcmp(readFunc+1, "cikis") == 0 || strcmp(readFunc+1, ":q") == 0){
                    CLOSE_APP("\n\nUygulamadan cikiliyor...", 0);
                }

                else if(strcmp(readFunc+1, "hataIleCikis") == 0){
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
                    system("cls");
                    CLOSE_APP(readStr+1 , 1);
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
                    char *newFs = malloc(BUFFER_SIZE); 
                    newFs[0] = ' ';
                    newFs[1] = '\0';
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer == ' '){
                        if(currentLineChar > strlen(currentLine)){break;}
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                            
                    //run this after the while is executed
                        
                    currentBuffer = currentLine[currentLineChar];
                    append_char(newFs, currentBuffer);

                    while(currentBuffer != ' '){
                        if(currentLineChar > strlen(currentLine)-1){break;}
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                        append_char(newFs, currentBuffer);
                    }

                    GET_INPUT(newFs+1);
                    free(newFs);
                }

                else if(strcmp(readFunc+1, "deger") == 0){
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

                if(strcmp(readFunc+1, "ekle") == 0){
                    char *newFs = malloc(BUFFER_SIZE); 

                    if(strlen(newFs) > 1){
                        newFs[1] = '\0';
                        newFs[2] = '\0';
                    }

                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                    while(currentBuffer == ' '){
                        if(currentLineChar > strlen(currentLine)){break;}
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                    }
                            
                    //run this after the while is executed
                        
                    currentBuffer = currentLine[currentLineChar];
                    append_char(newFs, currentBuffer);

                    while(currentBuffer != ' '){
                        if(currentBuffer == '\n'){break;}
                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];
                        append_char(newFs, currentBuffer);
                    }
                    newFs[strlen(newFs) - 1] = '\0';
                    COMPILE(newFs+1);
                    free(newFs);
                }
            }
        }
    }
    free(file);
    free(compileFile);
}
