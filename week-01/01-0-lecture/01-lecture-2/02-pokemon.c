#include <stdio.h>

// Andrew Taylor - andrewt@unsw.edu.au
// 16/9/2019
// Represent a small set of possible values using bits


#define FIRE_TYPE      0x0001
#define FIGHTING_TYPE  0x0002
#define WATER_TYPE     0x0004
#define FLYING_TYPE    0x0008
#define POISON_TYPE    0x0010
#define ELECTRIC_TYPE  0x0020
#define GROUND_TYPE    0x0040
#define PSYCHIC_TYPE   0x0080
#define ROCK_TYPE      0x0100
#define ICE_TYPE       0x0200
#define BUG_TYPE       0x0400
#define DRAGON_TYPE    0x0800
#define GHOST_TYPE     0x1000
#define DARK_TYPE      0x2000
#define STEEL_TYPE     0x4000
#define FAIRY_TYPE     0x8000

int main(void) {
    // give our pokemon 3 types
    int pokemon_type = BUG_TYPE|POISON_TYPE|FAIRY_TYPE;

    printf("0x%04x\n", pokemon_type);

    if (pokemon_type & POISON_TYPE) {
        // true since it is non-zero
        printf("Danger poisonous\n"); // prints
    }

    if (pokemon_type & GHOST_TYPE) {
        // false because it is 0
        printf("Scary\n"); // does not print
    }
}