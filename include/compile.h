#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

//funcMode checks if the file is being read from a function file or normal file
//0 equals normal reading
//1 equals function (so it will check for &'s)
void COMPILE(char *compileFile, int funcMode){
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

            while(currentBuffer == ' '){ //for tabs in the beginning of the line
                currentLineChar++;
                currentBuffer = currentLine[currentLineChar];
            }


            if(readMode == 0){
                int b = 0;
                int s = 0;
                int k = 0; /*değer okuyucu*/
                for(; b < strlen(currentLine); b++){
                    if(currentLine[b] == ';'){
                        if(currentLine[b-1] != '%')s++;
                        else memmove(&currentLine[b - 1], &currentLine[b], strlen(currentLine) - b - 1);
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
                    currentLine[bb] == '/'){
                        if(currentLine[bb - 1] != '%') ss++;
                        else{
                            memmove(&currentLine[bb - 1], &currentLine[bb], strlen(currentLine) - bb - 1);
                        }
                    }
                }
                while(kk < ss){
                    kk++;
                    
                    int fn = 0; //first number
                    int sn = 0; //second number
                    int ys = 0;

                    char *fnc = malloc(512); //first number as text
                    char *snc = malloc(512); //second number as text
                    char *ttr = malloc(512); //text to replace
                    char *operator = malloc(8); //operator


                    fnc[0] = ' ';
                    snc[0] = ' ';
                    ttr[0] = ' ';
                    operator[0] = ' ';

                    if(strlen(fnc) > 1){
                        fnc[1] = '\0';
                        fnc[2] = '\0';
                    }
                    if(strlen(ttr) > 1){
                        ttr[1] = '\0';
                        ttr[2] = '\0';
                    }
                    if(strlen(operator) > 1){
                        operator[1] = '\0';
                        operator[2] = '\0';
                    }

                    snc[1] = '0';
                    snc[2] = '\0';

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

                        if(currentLine[currentLineChar + 1] != '+' && currentLine[currentLineChar + 1] != '-' && currentLine[currentLineChar + 1] != '*'){
                            operator[1] = currentBuffer; //set operator
                            operator[2] = '\0';
                        }
                        else{
                            operator[1] = currentBuffer;
                            operator[2] = currentLine[currentLineChar + 1];
                            operator[3] = '\0';
                            
                            ss--;
                            
                            append_char(ttr, currentLine[currentLineChar+1]);

                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }

                        currentLineChar++;
                        currentBuffer = currentLine[currentLineChar];

                        while(currentBuffer == ' '){
                            append_char(ttr, currentBuffer);
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }

                        if(strcmp(operator+1, "++") != 0 && strcmp(operator+1, "--") != 0){
                            ys = 0;
                        }else{
                            ys = 1;
                        }

                        while(currentBuffer != ' ' && currentBuffer != '"'){
                            if(currentLineChar > strlen(currentLine) - 1){break;}
                            if(ys == 0){append_char(snc, currentBuffer);}
                            append_char(ttr, currentBuffer);
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar]; 
                        }
                    }
                    char result[BUFFER_SIZE];
                    intToStr(NUMBER_CALCULATION(atoi(fnc+1), atoi(snc+1), operator+1), result);

                    char *res = str_replace(currentLine, ttr+1, result);
                    
                    sprintf(currentLine, "%s", res);
                    
                    free(res);
                    free(fnc);
                    free(snc);
                    free(ttr);
                    free(operator);
                }

                currentLineChar = 0;
                currentBuffer = currentLine[currentLineChar];

                while(currentBuffer == ' '){ //for tabs in the beginning of the line
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                }
                                    
                if(currentBuffer != ' '){
                    if(currentLineChar > 1 && currentLine[currentLineChar-1] != ' '){
                        currentLineChar--;
                        currentBuffer = currentLine[currentLineChar];
                    } //i mean, it works
                    
                    //trying to find a function
                    
                    while(strcmp(readFunc+1, "yazdir") != 0 && strcmp(readFunc+1, "dosyayaEkle") != 0 && strcmp(readFunc+1, "dosyayaYaz") != 0 && strcmp(readFunc+1, "cikis") != 0 && strcmp(readFunc+1, "hataIleCikis") && strcmp(readFunc+1, ":q") != 0 && strcmp(readFunc+1, "dosyaOku") != 0 && strcmp(readFunc+1, "satirOku") != 0 && strcmp(readFunc+1, "yeniSatir") != 0 && strcmp(readFunc+1, "girdiAl") != 0 && strcmp(readFunc+1, "deger") != 0 && strcmp(readFunc+1, "ekle") != 0 && strcmp(readFunc+1, "yeniDeger") != 0 && strcmp(readFunc+1, "temizle") != 0 && strcmp(readFunc+1, "fonksiyon") != 0 && strcmp(readFunc+1, "silDeger") != 0 && strcmp(readFunc+1, "kullan") != 0 && strcmp(readFunc+1, "eger") != 0){ 
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
                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }
                                
                        //run this after the while is executed
                        currentLineChar++;
                        currentFuncChar = 1;
                            
                        currentBuffer = currentLine[currentLineChar];
                        
                        readStr[1] = currentBuffer;
                        readStr[0] = ' ';

                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
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
                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }

                        currentLineChar++;
                        currentFuncChar = 1;
                        currentBuffer = currentLine[currentLineChar];
                        
                        readFileName[1] = currentBuffer;
                        readFileName[0] = ' ';
                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
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
                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }

                        currentLineChar++;
                        currentFuncChar = 1;
                        currentBuffer = currentLine[currentLineChar];
                        
                        readFileName[1] = currentBuffer;
                        readFileName[0] = ' ';
                        while(currentBuffer != '"' && currentLineChar < strlen(currentLine)){
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

                    else if(strcmp(readFunc+1, "yeniDeger") == 0){
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
                                    int i = 0;
                                    while(i < varAmount){
                                        if(comparevar(varNames[i], readStr+1) == 0){
                                            strcpy(varValues[i], readFileName+1);
                                            break;
                                        }else{
                                            i++;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    else if(strcmp(readFunc+1, "silDeger") == 0){
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
                        }

                        if(readStr[strlen(readStr)-1] == '\n'){
                            readStr[strlen(readStr)-1] = '\0';
                        }


                        int i = 0;
                        while(i < varAmount){
                            if(strcmp(readStr+1, varNames[i]) == 0){
                                varNames[i][0] = '\0';
                                break;
                            }
                            i++;
                        }
                        
                    }

                    else if(strcmp(readFunc+1, "temizle") == 0){
                        system("cls");
                    }

                    else if(strcmp(readFunc+1, "ekle") == 0){
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
                        COMPILE(newFs+1, 0);
                        free(newFs);
                    }

                    else if(strcmp(readFunc+1, "fonksiyon") == 0){
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

                        while(currentBuffer != ' ' && currentBuffer != '('){
                            if(currentLineChar > strlen(currentLine)-1){break;}
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                            append_char(newFs, currentBuffer);
                        }
                        newFs[strlen(newFs) - 1] = '\0'; //function name
                        
                        char *newVals = malloc(BUFFER_SIZE);
                        newVals[0] = ' ';
                        newVals[1] = '\0';

                        while(currentBuffer != ')'){
                            if(currentLineChar > strlen(currentLine)){break;}
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                            append_char(newVals, currentBuffer);
                        }
                        newVals[strlen(newVals) - 1] = '\0';
                        
                        strcpy(functionNames[funcAmount], newFs+1);                        
                        strcpy(functionParameters[funcAmount], newVals+1);
                        readMode = 1;
                        funcReading = 1;
                        funcAmount++; //REMEMBER WE INCREASE IT HERE BUT WHILE READING FOR THE FUNCTION WE DECREASE IT BY 1
                    }

                    else if(strcmp(readFunc+1, "kullan") == 0){
                        char *newFs = malloc(BUFFER_SIZE); 
                        char *newVl = malloc(BUFFER_SIZE);
                        if(strlen(newFs) > 1){
                            newFs[1] = '\0';
                            newFs[2] = '\0';
                        }
                        if(strlen(newVl) > 1){
                            newVl[0] = ' ';
                            newVl[1] = '\0';
                            newVl[2] = '\0';
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
                        while(currentBuffer != ' ' && currentBuffer != '('){
                            if(currentBuffer == '\n'){break;}
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                            append_char(newFs, currentBuffer);
                        }
                        newFs[strlen(newFs) - 1] = '\0';
                        while(currentBuffer != '('){
                            if(currentLineChar > strlen(currentLine) - 1){break;}
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];   
                        }
                        if(currentBuffer == '('){
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                            while(currentBuffer != ')'){
                                if(currentLineChar > strlen(currentLine) - 1){break;}
                                append_char(newVl, currentBuffer);
                                currentLineChar++;
                                currentBuffer = currentLine[currentLineChar];
                            }
                            int h = 0;
                            for(; h < funcAmount+1; h++){
                                if(strcmp(newFs+1, functionNames[h]) == 0){
                                    break;
                                }
                            }
                            if(h < funcAmount+1){ //means that function was found in the array
                                char spred[25][25];
                                char spredBs[25][25];
                                for(int u = 0; u < 25; u++){
                                    for(int ul = 0; ul < 25; ul++){
                                        spredBs[u][ul] = '\0';
                                    }
                                }
                                int i = 0;

                                char *token = strtok(functionParameters[h], ",");
                                while(token != NULL && i < 20){
                                    strcpy(spred[i], token);
                                    i++;

                                    token = strtok(NULL, ",");
                                }

                                i = 0;
                                char *secondToken = strtok(newVl+1, ",");
                                while(secondToken != NULL && i < 20){
                                    for(int u = 0; u < strlen(secondToken); u++){
                                        spredBs[i][u] = secondToken[u];
                                        spredBs[i][u+1] = '\0';
                                    }
                                    i++;

                                    secondToken = strtok(NULL, ",");
                                }

                                int varamt = 0; //<- PARAMETER AMOUNT
                                int k = 0;
                                while(k < 25){
                                    if(strlen(spredBs[k]) == 0){break;}
                                    else{varamt++;}
                                    k++;
                                }   

                                char *temp = malloc(BUFFER_SIZE);
                                char *src = malloc(BUFFER_SIZE);

                                sprintf(temp, "%s_temp.h2o", functionNames[h]);
                                strcpy(src, temp);
                                                    
                                FILE *temporaryFunctionFile = fopen(temp, "w");
                                
                                for(int u = 0; u < varamt; u++){ //creates temporary variables
                                    char *tmp = malloc(BUFFER_SIZE);
                                    int src = 0; //0 means var name 1 means string

                                    for(int ul = 0; ul < strlen(spredBs[u]); ul++){
                                        if(spredBs[u][ul] == '"') src = 1;
                                    }
                                    if(src == 0){
                                        int k = 0;
                                        rmvspc(spredBs[u]);
                                        for(; k < varAmount+1; k++){
                                            if(strcmp(varNames[k], spredBs[u]) == 0) break;
                                        }
                                        if(k < varAmount+1){
                                            sprintf(tmp, "deger %s \"%s\"\n", spred[u], varValues[k]);
                                        }
                                    }
                                    else if(src == 1){
                                        sprintf(tmp, "deger %s %s\n", spred[u], spredBs[u]);
                                    }
                                    fprintf(temporaryFunctionFile, tmp);
                                    free(tmp);
                                }

                                fprintf(temporaryFunctionFile, functionVoid[h]); //prints main function
                                
                                for(int u = 0; u < varamt; u++){ //removes all temporary variables created
                                    char *tmp = malloc(BUFFER_SIZE);
                                    sprintf(tmp, "silDeger %s\n", spred[u]);
                                    fprintf(temporaryFunctionFile, tmp);
                                    free(tmp);
                                }

                                fclose(temporaryFunctionFile); //TODO DO silDeger FOR VALUES THAT WERE CREATED IN THE FUNCTION

                                COMPILE(temp, 0);
                                                    
                                remove(src);
                                free(temp);
                                free(src);
                                free(temporaryFunctionFile);

                                free(token);
                                free(secondToken);
                            }
                        }

                        free(newFs);
                        free(newVl);
                    }

                    else if(strcmp(readFunc+1, "eger") == 0){
                        char *firstVal = malloc(BUFFER_SIZE);  //first value in comprension
                        char *secondVal = malloc(BUFFER_SIZE); //second value in comprension
                        char *compare = malloc(BUFFER_SIZE);   //comprension
                        
                        firstVal[0] = ' ';
                        secondVal[0] = ' ';
                        compare[0] = ' ';

                        if(strlen(firstVal) > 1){
                            firstVal[1] = '\0';
                            firstVal[2] = '\0';
                        }
                        if(strlen(secondVal) > 1){
                            secondVal[1] = '\0';
                            secondVal[2] = '\0';
                        }
                        if(strlen(compare) > 1){
                            compare[1] = '\0';
                            compare[2] = '\0';
                        }

                        while(currentBuffer == ' '){
                            if(currentLineChar>strlen(currentLine)){break;}
                            currentLineChar++;
                            currentBuffer = currentLine[currentLineChar];
                        }
                        if(currentBuffer != ' '){ //start reading first variable
                            while(currentBuffer != ' '){
                                if(currentLineChar>strlen(currentLine)){break;}
                                append_char(firstVal, currentBuffer);
                                currentLineChar++;
                                currentBuffer = currentLine[currentLineChar];
                            }
                            if(currentBuffer == ' '){
                                while(currentBuffer == ' '){
                                    if(currentLineChar>strlen(currentLine)){break;}
                                    currentLineChar++;
                                    currentBuffer = currentLine[currentLineChar];
                                }
                                if(currentBuffer != ' '){ //start reading comprension
                                    while(currentBuffer != ' '){
                                        if(currentLineChar>strlen(currentLine)){break;}
                                        append_char(compare, currentBuffer);
                                        currentLineChar++;
                                        currentBuffer = currentLine[currentLineChar];
                                    }
                                    if(currentBuffer == ' '){
                                        while(currentBuffer == ' '){
                                            if(currentLineChar>strlen(currentLine)){break;}
                                            currentLineChar++;
                                            currentBuffer = currentLine[currentLineChar];
                                        }
                                        if(currentBuffer != ' '){ //start reading second variable
                                            while(currentBuffer != ' ' && currentBuffer != '{' && currentLineChar < strlen(currentLine)){
                                                append_char(secondVal, currentBuffer);
                                                currentLineChar++;
                                                currentBuffer = currentLine[currentLineChar];
                                            }
                                            if(currentBuffer == ' ' || currentBuffer == '{' || currentLineChar == strlen(currentLine)){
                                                //here, check if variables entered are variables or strings
                                                if(firstVal[1] != '"'){
                                                    int i = 0;
                                                    while(i < varAmount){
                                                        if(comparevar(varNames[i], firstVal+1) == 0){
                                                            sprintf(firstVal+1, "%s", varValues[i]);
                                                            break;
                                                        }else{
                                                            i++;
                                                        }
                                                    }
                                                }
                                                else if(firstVal[1] == '"'){
                                                    remove_char(firstVal+1, '"');
                                                }
                                                if(secondVal[1] != '"'){
                                                    int i = 0;
                                                    while(i < varAmount){
                                                        if(comparevar(varNames[i], secondVal+1) == 0){
                                                            sprintf(secondVal+1, "%s", varValues[i]);
                                                            break;
                                                        }else{
                                                            i++;
                                                        }
                                                    }
                                                }
                                                else if(secondVal[1] == '"'){
                                                    remove_char(secondVal+1, '"');
                                                }
                                                if(secondVal[strlen(secondVal) - 1] == '\n'){
                                                    secondVal[strlen(secondVal) - 1] = '\0';
                                                }

                                                if(strcmp(compare+1, "esittir") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) == atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) == atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                    else{
                                                        if(strcmp(firstVal+1, secondVal+1) == 0){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                }
                                                else if(strcmp(compare+1, "!esittir") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) != atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) != atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }   
                                                    }
                                                    else{
                                                        if(strcmp(firstVal+1, secondVal+1) != 0){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                }
                                                else if(strcmp(compare+1, "kucuktur") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) < atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) < atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                    else{
                                                        if(funcReading == 1) readMode = 1;
                                                        else readMode = 2;
                                                    }
                                                }
                                                else if(strcmp(compare+1, "buyuktur") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) > atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) > atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                    else{
                                                        if(funcReading == 1) readMode = 1;
                                                        else readMode = 2;
                                                    }
                                                }
                                                else if(strcmp(compare+1, "kucukesittir") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) <= atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) <= atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                    else{
                                                        if(funcReading == 1) readMode = 1;
                                                        else readMode = 2;
                                                    }
                                                }
                                                else if(strcmp(compare+1, "buyukesittir") == 0){
                                                    if(atoi(firstVal+1) == 0 && strcmp(firstVal+1, "0") == 0 && atoi(secondVal+1) == 0 && strcmp(secondVal+1, "0") == 0){
                                                        if(atoi(firstVal+1) >= atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }else if(atoi(firstVal+1) != 0 || atoi(secondVal+1) != 0){
                                                        if(atoi(firstVal+1) >= atoi(secondVal+1)){
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 0;
                                                        }else{
                                                            if(funcReading == 1) readMode = 1;
                                                            else readMode = 2;
                                                        }
                                                    }
                                                    else{
                                                        if(funcReading == 1) readMode = 1;
                                                        else readMode = 2;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        free(firstVal);
                        free(secondVal);
                        free(compare);
                    }
                }
            }
            
            else if(readMode == 1){
                funcReading = 1;
                if(currentBuffer != '}'){
                    strcat(functionVoid[funcAmount - 1], currentLine);
                }
                else{
                    funcReading = 0;
                    readMode = 0;
                }
            }

            else if(readMode == 2){
                char *tmp = malloc(30);
                tmp[0] = ' ';
                tmp[1] = '\0';
                tmp[2] = '\0';
                while(currentBuffer != ' '){
                    append_char(tmp, currentBuffer);
                    currentLineChar++;
                    currentBuffer = currentLine[currentLineChar];
                }
                if(strcmp(tmp+1, "bitir")){
                    readMode = 0;
                }else{
                    readMode = 2;
                }
                free(tmp);
            }
        }
    
    }
    fclose(file);
    free(file);
    free(compileFile);
}
