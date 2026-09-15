//packager.cpp
#include <string>
#include <array>
#include "../h_files/global.h"
#include "../h_files/depot.h"
#include <englishModule.h>
#include <germanModule.h>
#include <hindiModule.h>
#include <marathiModule.h>

void DispatchPackage(Package package){
    RecievePackage(package);
}

void startPackaging(char inputArray[]){

    English::beginTranslation();
    German::beginTranslation();
    Hindi::beginTranslation();
    Marathi::beginTranslation();

    int size = 0; //ignores the first '\0'
    while (inputArray[size] != '\0'){
        size++;
    }

    //sample demo array = ['8', '9', '1', '\0']
    int currentPosition = 0;
    for (int i = size-1; i >= 0; i--){
        Package package;
        package.currentNumber = inputArray[i];
        if (i != 0) {package.nextNumber = inputArray[i-1];}
        else package.nextNumber = '\0';
        
        package.position = currentPosition; //0 = unit, 1 = tens, 2 = hundred and so on
        currentPosition++;

        DispatchPackage(package);

    }
}


