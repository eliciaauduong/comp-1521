# Lecture 1 Notes
Thursday September 26, 2019

## Floating Point Numbers

Example of normalising the fraction part in binary:
- 1010.1011 is normalised as 1.0101011 × 2<sup>011</sup>
- 1010.1011 = 10 + 11/16 = 10.6875
- 1.0101011 × 2<sup>011</sup> 
= (1 + 43/128) × 2<sup>3</sup> 
= 1.3359375 × 8 
= 10.6875

The normalised fraction part always has 1 before the decimal point.

Example of determining the exponent in binary:
- Assume an 8-bit exponent, then bias B = 2<sup>8 - 1</sup> - 1 = 127
- Valid bit patterns for exponent: 00000001 .. 11111110
- Exponent values -126 .. 127