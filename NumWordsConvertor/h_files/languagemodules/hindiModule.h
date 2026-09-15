#ifndef HINDI_MODULE
#define HINDI_MODULE

#include <global.h>
#include <string>
#include <array>
namespace Hindi{

void beginTranslation();
void n2wTranslator(Package package);
void w2nTranslator(char inputArray[]);
}
#endif