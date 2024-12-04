#ifndef PUZZLE1
#define PUZZLE1

typedef struct {
    int start;
    int end;
} Match;

char* readFile(char* path); // Return a pointer to the string of text
void regexForMult(char* fileContent); // Return a pointer to a string array with each being a mult call
int mul(int a, int b);

#endif