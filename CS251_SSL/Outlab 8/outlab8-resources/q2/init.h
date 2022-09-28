#include <iostream>
#include <string.h>
using namespace std;

struct ans {
    int isValid;
    string* answer;
};

// initializes the part
void init(char* s, int part);

// return the answer
string  load_var();

// returns an array that contains the answer
string* load_arr();

// copies over the answer to address 's' at an offset
void    load_mem(char* s);

// loads the answer into the provided struct
void    load_struct(struct ans* a);
