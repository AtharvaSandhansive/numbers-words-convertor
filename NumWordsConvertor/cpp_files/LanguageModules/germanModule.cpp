#include <string>
#include <array>
#include <global.h>
#include <depot.h>
#include <parser.h>
#include <normalizer.h>

namespace German{
    inline const Container GERMAN_DATASET[] = {
        //1 to 9
        {0, "null"},
        {1, "eins"},
        {2, "zwei"},
        {3, "drei"},
        {4, "vier"},
        {5, "fuenf"},      
        {6, "sechs"},
        {7, "sieben"},
        {8, "acht"},
        {9, "neun"},

        // 10 to 19
        {10, "zehn"},
        {11, "elf"},
        {12, "zwoelf"},    
        {13, "dreizehn"},
        {14, "vierzehn"},
        {15, "fuenfzehn"}, 
        {16, "sechzehn"},
        {17, "siebzehn"},
        {18, "achtzehn"},
        {19, "neunzehn"},

        // Multiples of Ten (20 to 90)
        {20, "zwanzig"},
        {30, "dreissig"},   //21
        {40, "vierzig"}, //22
        {50, "fuenfzig"},   //23
        {60, "sechzig"}, //24
        {70, "siebzig"}, //25
        {80, "achtzig"}, //26
        {90, "neunzig"}, //27

        // Power Scale Values
        {100, "hundert"}, //28
        {1000, "tausend"}, //29
        {1000000, "million"}, //30
        {-1, "und"}
    };

    const int GERMAN_DATASET_SIZE = sizeof(GERMAN_DATASET) / sizeof(GERMAN_DATASET[0]);

    std::string final_string = "";
    void exportString(std::string outputStr){
        if (final_string=="") {final_string += GERMAN_DATASET[0].word;}
        CollectPackages(outputStr, GERMAN);
    }

    int unitTensSum = 0;
    
    void beginTranslation(){unitTensSum = 0; setValidity(true); final_string.clear();}

    void applyPower(std::string &result, int pos){
        if (result.empty()){
            return;
        }
        
        if (pos >= 3 && pos <= 5)
        {
            result += GERMAN_DATASET[29].word;   // tausend
        }
        else if (pos >= 6 && pos <= 8)
        {
            result += GERMAN_DATASET[30].word;   // million
        }
    }

    void appendResult(std::string &result){
        final_string = result + final_string;
    }

    void n2wTranslator(Package package) {
        
        int currentNumber = package.currentNumber - '0'; //convert current no. char into integr

        int position = package.position;
        int nextNumber=-1;
        if (package.nextNumber != '\0') {
            nextNumber = package.nextNumber - '0';//convert next no. char to integr
        }

        std::string result = "";

        bool isUnit = position==0||position==3||position==5||position==7;
        if (isUnit){
            if (package.nextNumber == '\0'){ //if only units
                result += GERMAN_DATASET[currentNumber].word;
                unitTensSum += currentNumber;
                applyPower(result,position);
                appendResult(result);
            }
            else if (nextNumber==0){ //if tens place = 0
                if (currentNumber != 0) {
                    result += GERMAN_DATASET[currentNumber].word;}
                if (position == 0) {unitTensSum += currentNumber;}
                applyPower(result, position);
                appendResult(result);
            }
            else if (nextNumber == 1){ //if tens place = 1
                result += GERMAN_DATASET[currentNumber+10].word;
                if (position==0){
                    unitTensSum += nextNumber*10+currentNumber;
                }
                applyPower(result,position);
                appendResult(result);
            }
            else {
                for (int i = 0; i < GERMAN_DATASET_SIZE; i++){
                    if ((nextNumber*10) == GERMAN_DATASET[i].integer){
                        
                        if(currentNumber != 0){
                            result += GERMAN_DATASET[currentNumber].word + "und";
                        }
                        result += GERMAN_DATASET[i].word;
                        applyPower(result, position);

                        if(position == 0){
                            unitTensSum += nextNumber*10 + currentNumber;
                        }
                        appendResult(result);
                    }
                }
            }
        }

        
        if (position==2 && currentNumber!=0){
            result += GERMAN_DATASET[currentNumber].word;
            result += GERMAN_DATASET[28].word;

            final_string = result + final_string;
        }
        
    
        if (package.nextNumber == '\0') {exportString(final_string);}
    }  
    
    void w2nTranslator(char inputArray[]){
        for (int i = 0; inputArray[i] != '\0'; i++) {
            inputArray[i] = normalize(inputArray[i]);
        }
        std::string tokenizedArray[100];
        GreedyParse(inputArray, GERMAN_DATASET, GERMAN_DATASET_SIZE, tokenizedArray);
        int numArray[50];
        int numArrayIndex = 0;
        int final_result = 0;
        int group = 0;
        if (isValid){

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < GERMAN_DATASET_SIZE; j++){
                    if (tokenizedArray[i] == GERMAN_DATASET[j].word){
                        int t = GERMAN_DATASET[j].integer;
                        numArray[numArrayIndex++] = t;
                        break;
                    }
                }
            }
            
            for (int i =0; i < numArrayIndex; i++){
                if (numArray[i] == -1) {
                    continue;
                }
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
1. The backward rule: From 21 to 99, the wording is structured as;
[unit place] + "und" + [tens place] if unit != 0, ex. 22-> einundzwanzig 
[tens place] -> assigned if unit = 0 ex. 20 -> zwanzig
2. Always assign ein whenever 1 comes; check in last for the result array,
if only ein is there, add the helper 's' at end to make it eins
3. No space is given; the words compound themselve to form large single word
4. For 1 million numbers use Million, add e to suffix of ein
For >1 face value at millionth place use Millionen
5. Uses international grouping system meaning groups of threes are made from right to left
*/