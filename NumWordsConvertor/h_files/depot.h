#ifndef DEPOT
#define DEPOT

#include <string>
#include <array>
#include "../h_files/global.h"

void CollectPackages(std::string str, LanguageSelected language);
void Translate();
void DeliverStrings(char inputArray[]);
void RecievePackage(Package recievedPackage);


#endif