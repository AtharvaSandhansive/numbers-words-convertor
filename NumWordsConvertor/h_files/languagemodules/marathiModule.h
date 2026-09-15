#ifndef MARATHI_MODULE
#define MARATHI_MODULE

#include <global.h>
#include <string>
#include <array>
namespace Marathi{

void beginTranslation();
void n2wTranslator(Package package);
void w2nTranslator(char inputArray[]);
}
#endif