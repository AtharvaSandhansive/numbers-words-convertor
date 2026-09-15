#include <string>
#include <array>
#include <global.h>
#include <depot.h>
#include <normalizer.h>
#include <parser.h>


namespace English{

    inline const Container ENGLISH_DATASET[] = {
        // 0 to 9
        {0, "zero"},
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"},

        // 10 to 19
        {10, "ten"},
        {11, "eleven"},
        {12, "twelve"},
        {13, "thirteen"},
        {14, "fourteen"},
        {15, "fifteen"},
        {16, "sixteen"},
        {17, "seventeen"},
        {18, "eighteen"},
        {19, "nineteen"},

        // Multiples of Ten (20 to 90)
        {20, "twenty"},
        {30, "thirty"}, //21
        {40, "forty"}, //22
        {50, "fifty"}, //23
        {60, "sixty"}, //24
        {70, "seventy"}, //25
        {80, "eighty"}, //26
        {90, "ninety"}, //27

        // Power Scale Values
        {100, "hundred"}, //28
        {1000, "thousand"}, //29
        {100000, "lakh"}, //30
        {10000000, "crore"} //31
    };

    std::string final_string = "";
    void exportString(std::string outputStr){
        if (final_string=="") {final_string += ENGLISH_DATASET[0].word;}
        CollectPackages(outputStr, ENGLISH);
    }

    const int ENGLISH_DATASET_SIZE = sizeof(ENGLISH_DATASET) / sizeof(ENGLISH_DATASET[0]);
    
    int unitTensSum = 0;
    
    void beginTranslation(){unitTensSum = 0;}

    void applyPower(std::string &result, int pos){
        if (result.empty()){
            return;
        }
        
        if (pos==3||pos==4){
            result += " " + ENGLISH_DATASET[29].word;
        }
        else if (pos==5||pos==6){
            result += " " + ENGLISH_DATASET[30].word;
        }
        else if (pos==7||pos==8){
            result += " " + ENGLISH_DATASET[31].word;
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
                result += " " + ENGLISH_DATASET[currentNumber].word;
                unitTensSum += currentNumber;
                applyPower(result,position);
                appendResult(result);
            }
            else if (nextNumber==0){ //if tens place = 0
                if (currentNumber != 0) {
                    result += " " + ENGLISH_DATASET[currentNumber].word;}
                if (position == 0) {unitTensSum += currentNumber;}
                applyPower(result, position);
                appendResult(result);
            }
            else if (nextNumber == 1){ //if tens place = 1
                result += " " + ENGLISH_DATASET[currentNumber+10].word;
                if (position==0){
                    unitTensSum += nextNumber*10+currentNumber;
                }
                applyPower(result,position);
                appendResult(result);
            }
            else {
                for (int i = 0; i < ENGLISH_DATASET_SIZE; i++){
                    if ((nextNumber*10) == ENGLISH_DATASET[i].integer){
                        result += " " + ENGLISH_DATASET[i].word;
                        if(currentNumber != 0){
                            result += " " + ENGLISH_DATASET[currentNumber].word;
                        }
                        applyPower(result, position);

                        if(position == 0){
                            unitTensSum += nextNumber*10 + currentNumber;
                        }
                        appendResult(result);
                    }
                }
            }
        }
        if (position == 2) {
          //  std::cout << "unitTensSum = " << unitTensSum << '\n';
        }

        
        if (position==2 && currentNumber!=0){
            if (unitTensSum != 0){
                result += " " + ENGLISH_DATASET[currentNumber].word + " " + 
                ENGLISH_DATASET[28].word + " " + "and";
                final_string = result + final_string;
            }
            else {
                result += " " + ENGLISH_DATASET[currentNumber].word + " " +
                ENGLISH_DATASET[28].word;
                final_string = result + final_string;
            }
            unitTensSum=0;
        }
        
    
        if (package.nextNumber == '\0') {exportString(final_string);}
    }   


    void w2nTranslator(char inputArray[]){
        for (int i = 0; inputArray[i] != '\0'; i++) {
        inputArray[i] = normalize(inputArray[i]);
        }
        std::string tokenizedArray[100];
        WhitespaceParser(inputArray, ENGLISH_DATASET, ENGLISH_DATASET_SIZE, tokenizedArray);
        int numArray[50];
        int numArrayIndex = 0;
        int final_result = 0;
        int group = 0;
        if (isValid){

            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < ENGLISH_DATASET_SIZE; j++){
                    if (tokenizedArray[i] == ENGLISH_DATASET[j].word){
                        int t = ENGLISH_DATASET[j].integer;
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

/*Semantics and rules
Sample array: [8, 7, 6, 5, 4, 3, 2, 1, 0] (the number decrease according to place value)
1. 0-19: Print directly ex. 17 -> Seventeen
2. 20-99: Print the tenth digit first and then unit ex. 22 -> 20 + 2 -> Twenty Two
3. Groupings occur as; positions [0] and [1] for unit, [3] and [4] for thousands, 
[5] and [6] for lakhs, [7] and [8] for crores. 
4. For [i+1][i] if [i+1] = 1, then Irregularity Handling Protocol (IHP) triggered. Based on the 
[i] value the word from ten to nineteen is assigned
5. If 0 is encountered IHP is triggered, the next int is peeped. This jumps occur everytime
whenever a 0 occurs. ex. for 0800, [0] = 0 next int peeped, [1] = 0 next int peeped,
[2] = 8 -> on hundredth place so 800, [3] = 0 next int peeped; no next int, end of array,
operation terminated. For 0000, [0] next peeped, [1] next peeped , [2] next peeped,
end of array, operation terminated. Result array is empty, Zero inserted in this case.
6. Word "and" is used after Hundred if tens and unit values are non zero

*/