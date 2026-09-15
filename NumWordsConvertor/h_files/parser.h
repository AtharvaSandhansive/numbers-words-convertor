//parser.h
#ifndef PARSER
#define PARSER
#include <string>
#include <array>
#include <global.h>

void setValidity(bool value);
bool isValid();
void WhitespaceParser(const char input[], const Container dataset[], 
    int datasetSize, std::string tokenizedArray[]);
void GreedyParse(const char input[], const Container dataset[], 
    int datasetSize, std::string tokenizedArray[]);

#endif