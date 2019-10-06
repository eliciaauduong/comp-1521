#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <float.h>
#include <assert.h>

void display_float(float value);
uint32_t get_float_bits(float f);
void print_float_bits(uint32_t bits);
void print_bits(uint32_t value, int high, int low);
void print_float_details(uint32_t bits);
uint32_t extract_bit_range(uint32_t value, int high, int low);

int main(int argc, char *argv[]) {
    for (int arg = 1; arg < argc; arg++) {
        printf("arg[%d] = \"%s\"\n", arg, argv[arg]);
        display_float(strtof(argv[arg], NULL));
    }
    return 0;
}


#define SIGN_BIT           31
#define EXPONENT_HIGH_BIT  30
#define EXPONENT_LOW_BIT   23
#define FRACTION_HIGH_BIT  22
#define FRACTION_LOW_BIT    0

#define EXPONENT_OFFSET   127
#define EXPONENT_INF_NAN  255

void display_float(float number) {
    uint32_t bits = get_float_bits(number);

    print_float_bits(bits);

    print_float_details(bits);
}

// For en explnation of calculation see:
// https://en.wikipedia.org/wiki/Single-precision_floating-point_format

void print_float_details(uint32_t bits) {
    uint32_t sign_bit = extract_bit_range(bits, SIGN_BIT, SIGN_BIT);
    uint32_t fraction_bits = extract_bit_range(bits, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    uint32_t exponent_bits = extract_bit_range(bits, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);

    int sign_char = sign_bit ? '-' : '+'; // if sign_bit ? then '-' : else '+'
    int exponent = exponent_bits - EXPONENT_OFFSET;

    printf("sign = %c \n", sign_char);
    printf("raw exponent = %d\n", exponent_bits);

    int implicit_bit = 1;

    // handle special cases of +infinity, -infinity
    // and Not a Number (NaN)
    if (exponent_bits == EXPONENT_INF_NAN) {
        if (fraction_bits == 0) {
            printf("number = %cinf\n", sign_char);
        } else {
            // https://en.wikipedia.org/wiki/NaN
            printf("number = NaN\n");
        }
        return;
    }

    if (exponent_bits == 0) {
        // if the exponent_bits are zero its a special case
        // called a denormal number
        // https://en.wikipedia.org/wiki/Denormal_number
        implicit_bit = 0;
        exponent++;
    }

    printf("actual exponent = %d - %d = %d\n", exponent_bits, EXPONENT_OFFSET, exponent);


    printf("number = %c%d.", sign_char, implicit_bit);
    print_bits(bits, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    printf("b * 2**%d\n", exponent);

    int fraction_size = FRACTION_HIGH_BIT - FRACTION_LOW_BIT + 1;
    double fraction_max = ((uint32_t)1) << fraction_size;
    double fraction = implicit_bit + fraction_bits / fraction_max;

    printf("       = %g * %g\n", fraction, exp2(exponent));
    printf("       = %g\n", fraction * exp2(exponent));
}

union overlay_float {
    float    f;
    uint32_t  u;
};

// return the raw bits of a float
uint32_t get_float_bits(float f) {
    union overlay_float overlay;
    overlay.f = f;
    return overlay.u;
}

// print out the bits of a float
void print_float_bits(uint32_t bits) {
    printf("sign | exponent |  fraction\n");
    printf("   ");
    print_bits(bits, SIGN_BIT, SIGN_BIT);
    printf(" | ");
    print_bits(bits, EXPONENT_HIGH_BIT, EXPONENT_LOW_BIT);
    printf(" | ");
    print_bits(bits, FRACTION_HIGH_BIT, FRACTION_LOW_BIT);
    printf("\n");
}

// print the binary representation of a value
void print_bits(uint32_t value, int high, int low) {
    for (int i = high; i >= low; i--) {
        int bit = extract_bit_range(value, i, i);
        printf("%d", bit);
    }
}

// extract a range of bits from a value
uint32_t extract_bit_range(uint32_t value, int high, int low) {
    uint32_t mask = (((uint32_t)1) << (high - low + 1)) - 1;
    return (value >> low) & mask;
}