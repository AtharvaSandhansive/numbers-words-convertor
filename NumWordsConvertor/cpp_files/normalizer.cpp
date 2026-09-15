//normalizer.cpp
char normalize(char character){

    if (character >= 'A' && character <= 'Z'){
        int x = character;
        int s = x + 32;
        char y = s;
        return y;
    }
    else return character; 
}