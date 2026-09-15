//slicer.cpp
#include <string>
#include <array>


void slice(std::string inputStr, char destinationArray[]){
    
    //first finding the size of the string
    int lenth = 0;
    while (inputStr[lenth] != '\0'){
        lenth++;
    }

    
    for (int i = 0; i < lenth; i++){
        destinationArray[i] = inputStr[i];
    }

    destinationArray[lenth] = '\0';
} 