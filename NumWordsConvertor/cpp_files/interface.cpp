//interface.cpp
#include <iostream>
#include <string>
#include <array>
#include "../h_files/inputValidator.h"
#include "../h_files/slicer.h"
#include "../h_files/global.h"
#include "../h_files/depot.h"
#include "../h_files/packager.h"


//universal vars
// takes input from the user for the required number
std::string takeInput(){
    std::string i = "";
    std::cout << "Enter Input: ";
    std::getline(std::cin, i);
    return i;
}

int main(){
    //declarations of variables
    int modeSelectedIndex = 0;
    std::string inputString = "";
    char inputArray[100];
    int languageSelectionInput = 0;
    LanguageSelected languageSelected = ENGLISH;

    //ask user to select mode
    std::cout << "Do you want to: " << std::endl;
    std::cout << "COnvert num to word (1)" <<std::endl;
    std::cout << "COnvert word to num (2)" << std::endl;
    std::cout << "Translate word in different language (3)" <<std::endl; //last to be implemented
    std::cout << "End the program (any)" <<std::endl;
    std::cin >> modeSelectedIndex;
    //set the mode
    setMode(modeSelectedIndex);
    //terminate if user wishes to quit
    if (modeSelectedIndex != 1 && modeSelectedIndex != 2 && modeSelectedIndex !=3){
        std::cout << "turning off!";
        return 0;
    }
    //ask for language selection if mode 3 is selected
    if (modeSelectedIndex == 3){
        std::cout<< "Please select language from below: "<<std::endl;
        std::cout<< "English(1)\nGerman(2)\nMarathi(3)\nHidni(4)"<<std::endl;
        std::cout <<">>"; std::cin >> languageSelectionInput;
        std::cout << "Language Selected>> ";
        switch(languageSelectionInput){
            case 1: languageSelected = ENGLISH; std::cout<<"English"; break;
            case 2: languageSelected = GERMAN; std::cout<<"German"; break;
            case 3: languageSelected = MARATHI; std::cout<<"Marathi"; break;
            case 4: languageSelected = HINDI; std::cout<<"Hindi"; break;
            default: std::cout<<"Please input valid language mode!"; return 0;
    }
    //set the selected language in global.h
    setLanguage(languageSelected);
    }
    
    //take actual input
    std::cin.ignore();
    inputString = takeInput();
    
    //send the input to Slicer to make an array
    slice(inputString, inputArray);
    //send the array to validator
    if (!validateInput(inputArray, modeSelectedIndex)){
        std::cout << "Please enter a valid input!"<<std::endl;
        return 0;
    }

    //check for the input size
    int size = 0;
    while (inputString[size] != '\0') size++;
    if (size > 9 && modeSelectedIndex == 1){
        std::cout << "The input number is too big for the system!";
        return 0;
    }
    
    //routes inputARray to right module for selected mode
    switch (modeSelectedIndex){
        case 1: startPackaging(inputArray); break;
        case 2: DeliverStrings(inputArray); break;
        case 3: DeliverStrings(inputArray); Translate(); break;
    }

    for (int i = 0; i < 4; i++){
        if (languageOutput[i] != "") {
            std::cout<< languageOutput[i] << std::endl;
        }
    }

    std::cout << "Thank you for using, terminating normally";

    return 0;
}