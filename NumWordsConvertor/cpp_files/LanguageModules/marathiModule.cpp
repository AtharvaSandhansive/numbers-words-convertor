#include <string>
#include <array>
#include <global.h>
#include <depot.h>
#include <packager.h>
#include <parser.h>
#include <normalizer.h>

namespace Marathi{
    inline const Container MARATHI_DATASET[] = {
    // 0 - 9
    {0, "shunya"},
    {1, "ek"},
    {2, "don"},
    {3, "teen"},
    {4, "char"},
    {5, "paach"},
    {6, "sahaa"},
    {7, "saath"},
    {8, "aath"},
    {9, "nau"},

    // 10 - 19
    {10, "dahaa"},
    {11, "akraa"},
    {12, "baraa"},
    {13, "teraa"},
    {14, "chaudaa"},
    {15, "pandaraa"},
    {16, "solaa"},
    {17, "satraa"},
    {18, "athraa"},
    {19, "ekonvees"},

    // 20 - 29
    {20, "vees"},
    {21, "ekvees"},
    {22, "bavees"},
    {23, "tevees"},
    {24, "chovees"},
    {25, "panchvees"},
    {26, "sahvees"},
    {27, "sattavees"},
    {28, "atthavees"},
    {29, "ekontees"},

    // 30 - 39
    {30, "tees"},
    {31, "ektees"},
    {32, "battees"},
    {33, "tehtees"},
    {34, "chautees"},
    {35, "pastees"},
    {36, "chattees"},
    {37, "sadotees"},
    {38, "adatees"},
    {39, "ekonchaalis"},

    // 40 - 49
    {40, "chaalis"},
    {41, "ekkechaalis"},
    {42, "bechaalis"},
    {43, "trechaalis"},
    {44, "chaurechaalis"},
    {45, "panchechaalis"},
    {46, "sehechaalis"},
    {47, "sattechalis"},
    {48, "atthechaalis"},
    {49, "ekonpannas"},

    // 50 - 59
    {50, "pannas"},
    {51, "ekkavan"},
    {52, "baavan"},
    {53, "trepan"},
    {54, "choupan"},
    {55, "panchavan"},
    {56, "chappan"},
    {57, "sattavan"},
    {58, "atthavan"},
    {59, "ekonsath"},

    // 60 - 69
    {60, "sath"},
    {61, "eksashta"},
    {62, "baasashta"},
    {63, "tresashta"},
    {64, "chausashta"},
    {65, "pasashta"},
    {66, "sahasashta"},
    {67, "sadusashta"},
    {68, "adusashta"},
    {69, "ekonsattar"},

    // 70 - 79
    {70, "sattar"},
    {71, "ekhattar"},
    {72, "bahattar"},
    {73, "trehattar"},
    {74, "chauhattar"},
    {75, "panchattar"},
    {76, "shahahattar"},
    {77, "sattyhattar"},
    {78, "athyhattar"},
    {79, "ekonainshi"},

    // 80 - 89
    {80, "ainshi"},
    {81, "ekyaainshi"},
    {82, "byaainshi"},
    {83, "tryainshi"},
    {84, "chaurainshi"},
    {85, "panchainshi"},
    {86, "sahainshi"},
    {87, "satyaainshi"},
    {88, "atthainshi"},
    {89, "ekonnavvad"},

    // 90 - 99
    {90, "navvad"},
    {91, "ekyanou"},
    {92, "byanou"},
    {93, "tryanou"},
    {94, "chauryanou"},
    {95, "panchyanou"},
    {96, "shahanou"},
    {97, "sattyanou"},
    {98, "atthyanou"},
    {99, "navvyanou"},

    // Powers
    {100, "shambhar"}, //100
    {100, "she"}, //101
    {1000, "hazar"}, //102
    {100000, "lakh"}, //103
    {10000000, "crore"}, //104

    // Optional connector
    {-1, "aani"}
};

    const int MARATHI_DATASET_SIZE = sizeof(MARATHI_DATASET) / sizeof(MARATHI_DATASET[0]);

    std::string final_string = "";
    void exportString(std::string outputStr){
        if (final_string=="") {final_string += MARATHI_DATASET[0].word;}
        CollectPackages(outputStr, MARATHI);
    }
    
   int unitTensSum = 0;

void beginTranslation() {
    unitTensSum = 0;
    final_string.clear();
}

void applyPower(std::string &result, int pos) {
    if (result.empty())
        return;

    if (pos == 3 || pos == 4)
        result += " " + MARATHI_DATASET[102].word;      //hazar
    else if (pos == 5 || pos == 6)
        result += " " + MARATHI_DATASET[103].word;      //lakh
    else if (pos == 7 || pos == 8)
        result += " " + MARATHI_DATASET[104].word;      //crore
}

void appendResult(std::string &result) {
    final_string = result + final_string;
}

void n2wTranslator(Package package) {

    int currentNumber = package.currentNumber - '0';
    int position = package.position;

    int nextNumber = -1;
    if (package.nextNumber != '\0')
        nextNumber = package.nextNumber - '0';

    std::string result;

    bool isUnit = (position == 0 || position == 3 ||
                   position == 5 || position == 7);

    if (isUnit) {

        //sngle digit at end
        if (package.nextNumber == '\0') {

            result += " " + MARATHI_DATASET[currentNumber].word;

            if (position == 0)
                unitTensSum = currentNumber;

            applyPower(result, position);
            appendResult(result);
        }

        //multiple of 10s
        else if (nextNumber == 0) {

            if (currentNumber != 0)
                result += " " + MARATHI_DATASET[currentNumber].word;

            if (position == 0)
                unitTensSum = currentNumber;

            applyPower(result, position);
            appendResult(result);
        }

        //alue from 10–99
        else {

            int value = nextNumber * 10 + currentNumber;

            result += " " + MARATHI_DATASET[value].word;

            if (position == 0)
                unitTensSum = value;

            applyPower(result, position);
            appendResult(result);
        }
    }

    if (position == 2 && currentNumber != 0) {

        result += " " + MARATHI_DATASET[currentNumber].word;
        result += MARATHI_DATASET[101].word;   // sau

        final_string = result + final_string;

        unitTensSum = 0;
    }

    if (package.nextNumber == '\0')
    {exportString(final_string);}
}

    void w2nTranslator(char inputArray[]){
        for (int i = 0; inputArray[i] != '\0'; i++) {
        inputArray[i] = normalize(inputArray[i]);
        }
        std::string tokenizedArray[100];
        WhitespaceParser(inputArray, MARATHI_DATASET, MARATHI_DATASET_SIZE, tokenizedArray);
        int numArray[50];
        int numArrayIndex = 0;
        int final_result = 0;
        int group = 0;
        if (isValid){

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < MARATHI_DATASET_SIZE; j++){
                    if (tokenizedArray[i] == MARATHI_DATASET[j].word){
                        int t = MARATHI_DATASET[j].integer;
                        numArray[numArrayIndex++] = t;
                        break;
                    }
                }
            }
            
            for (int i =0; i < numArrayIndex; i++){
                if (numArray[i] < 100){
                    group += numArray[i];
                }
                else if (numArray[i] == 100){
                    if (group == 0){
                        group = 1;
                    }
                    group *= 100;
                }
                else{
                    final_result += group * numArray[i];
                    group = 0;
                }
            }
            final_result += group;

            exportString(std::to_string(final_result));
            
        } 
    }
}

/* Semantics and rules
1. If 1 is encountered at 100th place or [2] and if [1] and [0] are zero, put shambhar
If not, add the suffix she at end of the face value of number at [2]
2. Grouping is similar to English with groups of [0], [1] and [3], [4] and [5], [6] and [7] [8]
3. based on this group total number find the word the int 72 with [0], [1] -> pair, 
direct equivalent word of 72 assigned.
4. Same rules for Shunya as Zero in english

*/