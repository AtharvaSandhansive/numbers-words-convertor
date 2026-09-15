#ifndef ENGLISH_MODULE
#define ENGLISH_MODULE

#include <global.h>
#include <string>
#include <array>
namespace English{

void beginTranslation();
void n2wTranslator(Package package);
void w2nTranslator(char inputArray[]);
}
#endif