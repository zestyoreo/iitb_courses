#include "myengine.hpp"

int generateRandomNumber() {
    int iSecret;
    srand(time(NULL));
    return rand();
}
