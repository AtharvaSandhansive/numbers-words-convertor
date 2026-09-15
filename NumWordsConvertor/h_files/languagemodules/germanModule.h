#ifndef GERMAN_MODULE
#define GERMAN_MODULE

#include <global.h>
#include <string>
#include <array>
namespace German{

void beginTranslation();
void n2wTranslator(Package package);
void w2nTranslator(char inputArray[]);
}
#endif