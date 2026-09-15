//validator.cpp
#include <string>


bool validateInput(char inputArray[], int modeSelected){

    //read only library where first layer filter reads from
    char numberArray[11] = {'0',  '1', '2', '3', '4', '5', '6', '7', '8', '9', '\0'};
    char characterArray[55] = {' ', ',', 'A', 'B', 'C', 'D', 'E', 'F','G','H','I','J','K','L',
    'M','N', 'O', 'P', 'Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c','d','e','f', 'g', 'h', 'i', 'j', 'k','l','m','n','o','p','q','r','s','t',
    'u', 'v','w','x','y','z', '\0'};

    if (modeSelected == 1){
        for (int i = 0; inputArray[i] != '\0'; i++){
            char currentCharacter = inputArray[i];
            bool isCharacterValid = false;
            
            for (int j = 0; numberArray[j] != '\0'; j++){
                if (currentCharacter == numberArray[j]){
                    isCharacterValid = true;
                    break;
                }
            }

            if (!isCharacterValid) return false;
        }
        return true;
    }
    else if (modeSelected == 2 || modeSelected == 3){
        for (int i = 0; inputArray[i] != '\0'; i++){
            char currentCharacter = inputArray[i];
            bool isCharacterACharacter = false;

            for (int j = 0; characterArray[j] != '\0'; j++){
                if (currentCharacter == characterArray[j]){
                    isCharacterACharacter = true;
                    break;
                }
            }

            if (!isCharacterACharacter) return false;
        }
        return true;

    }
    else return false;

}