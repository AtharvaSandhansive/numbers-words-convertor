#include <string>
#include <array>
#include <depot.h>
#include <packager.h>
#include <global.h>
#include <iostream>
#include <normalizer.h>
#include <parser.h>

namespace Hindi{
    inline const Container HINDI_DATASET[] = {
    // 0 - 9
    {0, "shunya"},
    {1, "ek"},
    {2, "do"},
    {3, "teen"},
    {4, "char"},
    {5, "paanch"},
    {6, "chhah"},
    {7, "saat"},
    {8, "aath"},
    {9, "nau"},

    // 10 - 19
    {10, "das"},
    {11, "gyarah"},
    {12, "barah"},
    {13, "terah"},
    {14, "chaudah"},
    {15, "pandrah"},
    {16, "solah"},
    {17, "satrah"},
    {18, "atharah"},
    {19, "unnees"},

    // 20 - 29
    {20, "bees"},
    {21, "ikkees"},
    {22, "baees"},
    {23, "teees"},
    {24, "chaubees"},
    {25, "pachchees"},
    {26, "chhabbees"},
    {27, "sattaees"},
    {28, "athtaees"},
    {29, "untees"},

    // 30 - 39
    {30, "tees"},
    {31, "iktees"},
    {32, "battees"},
    {33, "taintees"},
    {34, "chauntees"},
    {35, "paintees"},
    {36, "chhattees"},
    {37, "saintees"},
    {38, "athtees"},
    {39, "untalees"},

    // 40 - 49
    {40, "chalees"},
    {41, "iktalees"},
    {42, "bayaalees"},
    {43, "taintalees"},
    {44, "chawaalees"},
    {45, "paintalees"},
    {46, "chhiyalees"},
    {47, "saintalees"},
    {48, "athtalees"},
    {49, "unchas"},

    // 50 - 59
    {50, "pachas"},
    {51, "ikyavan"},
    {52, "baavan"},
    {53, "tirpan"},
    {54, "chauvan"},
    {55, "pachpan"},
    {56, "chhappan"},
    {57, "sattavan"},
    {58, "atthavan"},
    {59, "unsath"},

    // 60 - 69
    {60, "saath"},
    {61, "iksat"},
    {62, "baasat"},
    {63, "tirsat"},
    {64, "chaunsat"},
    {65, "painsat"},
    {66, "chhiyasat"},
    {67, "satsat"},
    {68, "athsat"},
    {69, "unhattar"},

    // 70 - 79
    {70, "sattar"},
    {71, "ikhattar"},
    {72, "bahattar"},
    {73, "tihattar"},
    {74, "chauhattar"},
    {75, "pachhattar"},
    {76, "chhihattar"},
    {77, "satthatar"},
    {78, "athhatar"},
    {79, "unasi"},

    // 80 - 89
    {80, "assee"},
    {81, "ikyasee"},
    {82, "bayaasee"},
    {83, "tirasee"},
    {84, "chaurasee"},
    {85, "pachaasee"},
    {86, "chhiyaasee"},
    {87, "satyaasee"},
    {88, "athtyaasee"},
    {89, "navaasee"},

    // 90 - 99
    {90, "navbe"},
    {91, "ikyaanve"},
    {92, "bayaanve"},
    {93, "tiryaanve"},
    {94, "chauraanve"},
    {95, "pachaanve"},
    {96, "chhiyaanve"},
    {97, "satyaanve"},
    {98, "athtyaanve"},
    {99, "ninaanve"},

    // Powers
    {100, "sau"},
    {1000, "hazar"}, //101
    {100000, "lakh"}, //102
    {10000000, "crore"}, //103

    // Connector (for parsing)
    {-1, "aur"}
};

    std::string final_string = "";
    void exportString(std::string outputStr){
        if (final_string=="") {final_string += HINDI_DATASET[0].word;}
        CollectPackages(outputStr, HINDI);
    }

    const int HINDI_DATASET_SIZE = sizeof(HINDI_DATASET) / sizeof(HINDI_DATASET[0]);
    
   int unitTensSum = 0;

void beginTranslation() {
    unitTensSum = 0;
    final_string.clear();
}

void applyPower(std::string &result, int pos) {
    if (result.empty())
        return;

    if (pos == 3 || pos == 4)
        result += " " + HINDI_DATASET[101].word;      //hazar
    else if (pos == 5 || pos == 6)
        result += " " + HINDI_DATASET[102].word;      //lakh
    else if (pos == 7 || pos == 8)
        result += " " + HINDI_DATASET[103].word;      //crore
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

        // Single digit at end
        if (package.nextNumber == '\0') {

            result += " " + HINDI_DATASET[currentNumber].word;

            if (position == 0)
                unitTensSum = currentNumber;

            applyPower(result, position);
            appendResult(result);
        }

        // Exact multiple of 10
        else if (nextNumber == 0) {

            if (currentNumber != 0)
                result += " " + HINDI_DATASET[currentNumber].word;

            if (position == 0)
                unitTensSum = currentNumber;

            applyPower(result, position);
            appendResult(result);
        }

        // Any value from 10–99
        else {

            int value = nextNumber * 10 + currentNumber;

            result += " " + HINDI_DATASET[value].word;

            if (position == 0)
                unitTensSum = value;

            applyPower(result, position);
            appendResult(result);
        }
    }

    if (position == 2 && currentNumber != 0) {

        result += " " + HINDI_DATASET[currentNumber].word;
        result += " " + HINDI_DATASET[100].word;   // sau

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
        WhitespaceParser(inputArray, HINDI_DATASET, HINDI_DATASET_SIZE, tokenizedArray);
        int numArray[50];
        int numArrayIndex = 0;
        int final_result = 0;
        int group = 0;
        if (isValid){

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < HINDI_DATASET_SIZE; j++){
                    if (tokenizedArray[i] == HINDI_DATASET[j].word){
                        int t = HINDI_DATASET[j].integer;
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
1. If 1 is encountered at this places [2], [3], [5], [7] dont put 'ek'
If not print, the unitary value; ex. 123 is said sau pachchees while 223 is said;
do sau pachchees (do + sau)
2. Grouping is similar to English and Marathi
3. Same rules for Shunya as Zero in english

*/