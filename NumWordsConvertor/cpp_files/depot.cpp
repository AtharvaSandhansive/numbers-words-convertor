//depot.cpp
#include <string>
#include <array>
#include "../h_files/global.h"
#include <englishModule.h>
#include <hindiModule.h>
#include <marathiModule.h>
#include <germanModule.h>
#include <slicer.h>
#include <packager.h>
#include <global.h>


void CollectPackages(std::string str,LanguageSelected language){languageOutput[language] += str;}

void Translate(){
    char inputArray[100];
    for (int i =0; i < 4; i++){
        if (languageOutput[i]!="" && languageOutput[i]!="0"){
            slice(languageOutput[i], inputArray);
        }
    }
    LanguageSelected lan = getLanguage();

    Package package;
    startPackaging(inputArray);

    switch (lan){
        case ENGLISH: English::n2wTranslator(package); break;
        case GERMAN: German::n2wTranslator(package); break;
        case HINDI: Hindi::n2wTranslator(package); break;
        case MARATHI: Marathi::n2wTranslator(package); break;
    }
}

void DeliverStrings(char inputArray[]){
    //delivers the input array directly to the modules's w2n pipeline
    English::w2nTranslator(inputArray);
    German::w2nTranslator(inputArray);
    Hindi::w2nTranslator(inputArray);
    Marathi::w2nTranslator(inputArray);
}

void DeliverPackages(Package package){
    //delivers the package direcvtly to the modules's n2w pipeline
    English::n2wTranslator(package);
    German::n2wTranslator(package);
    Hindi::n2wTranslator(package);
    Marathi::n2wTranslator(package);
}

void RecievePackage(Package recievedPackage){DeliverPackages(recievedPackage);}




