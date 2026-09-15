//global.h
#ifndef GLOBAL
#define GLOBAL

#include <string>
#include <array>

struct Package
{
    char currentNumber;
    int position;
    char nextNumber;
};

struct Container
{
    int integer;
    std::string word;
};

enum LanguageSelected{
    ENGLISH,
    GERMAN,
    MARATHI,
    HINDI
};

extern std::string languageOutput[8];

extern int currentModeSelected;
extern LanguageSelected currentLanguageSelected;

inline void setMode(int mode){
    currentModeSelected = mode;
}

inline void setLanguage(LanguageSelected languageSelected){
    currentLanguageSelected = languageSelected;
}

inline int getMode() {return currentModeSelected; }
inline LanguageSelected getLanguage() {return currentLanguageSelected; }

#endif 
