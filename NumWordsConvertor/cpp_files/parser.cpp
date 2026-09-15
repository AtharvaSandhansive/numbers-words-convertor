//parser.cpp
#include <string>
#include <array>
#include <global.h>

bool validity = true;
void setValidity(bool value)
{
    validity = value;
}

bool isValid()
{
    return validity;
}

void WhitespaceParser(const char input[], const Container dataset[], 
    int datasetSize, std::string tokenizedArray[]){
    int size = 0;
    while (input[size] != '\0') {size++;}

    //sample input array = [s,i,x,t,y, ,s,i,x]
    std::string collector = "";
    std::string lastMatch = "";
    int tokenIndex = 0;
    for (int i = 0; i < size; i++){
        if (input[i] == ' '){
            if (collector != lastMatch){
                validity = false;
                return;
            }
            tokenizedArray[tokenIndex++] = lastMatch;

            collector.clear();
            lastMatch.clear();
            continue;
        }  

        collector += input[i];

        for (int j = 0; j < datasetSize; j++){
            if (collector == dataset[j].word){
                lastMatch = collector;
                break;
            }
        }
        
    }
    if (collector != lastMatch){
        validity = false;
        return;
    }

    if (!lastMatch.empty()){
        tokenizedArray[tokenIndex++] = lastMatch;
    }
    else {
        validity = false;
        return;
    }

}

void GreedyParse(const char input[], const Container dataset[], 
    int datasetSize, std::string tokenizedArray[]){
    
    int size = 0;
    while (input[size] != '\0') {size++;}

    int tokenIndex = 0;
    int i = 0; //starting point of the search window

    while (i < size){
        std::string collector = "";
        std::string lastMatch = "";
        int lastMatchIndex = -1; //tracks where last match ended

        for (int j = i; j < size; j++){
            collector += input[j];

            //check if the collected word exists till now in the dataset
            for (int k = 0; k < datasetSize; k++){
                if (collector == dataset[k].word){
                    lastMatch = collector;
                    lastMatchIndex = j;
                }
            }
        }
        //if last match is not empty
        if (!lastMatch.empty()){
            tokenizedArray[tokenIndex++] = lastMatch;
            i = lastMatchIndex + 1;
            //if last found word is zwei with i index being 3, jump directly to 3
        }
        else {//if not found
            //typos not tolerated like zweixzehn
            validity = false;
            return;
        }
    }

}