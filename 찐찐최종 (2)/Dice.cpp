#include "Dice.h"
#include <cstdlib>

int Dice::roll() {
    return rand() % 6 + 1;
}