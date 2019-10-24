# Lecture 1 Notes
Wednesday October 9, 2019

## Functions
When we call a function: 
- The arguments are evaluated and set up for function 
- Control is transferred to the code for the function
- Local variables are created
- The function code is executed in this environment 
- The return value is set up 
- Control transfers back to where the function was called from 
- The caller receives the return value

Each function allocates a small section of the stack (a *frame*) 
- Used for: saved registers, local variables, parameters to callees 
- Created in the function *prologue* (pushed) 
- Removed in the function *epilogue* (popped) 

Why we use a stack: 
- Function `f()` calls `g()` which calls `h()` 
- `h()` runs, then ﬁnishes and returns to `g()` 
- `g()` continues, then ﬁnishes and returns to `f()` 

i.e. last-called, exits-ﬁrst (last-in, ﬁrst-out) behaviour

Data associated with function calls is placed on the MIPS stack

``` 
            |--------------------------|
            |     Reserved (kernel)    |
0x7FFFFFFC  |__________________________|
            |           Stack          | # Stack frames for function calls
       $sp  |__________________________|
            |            |             |
            |            V             |
            |__________________________|
            |           Data           | # Program data
0x10000000  |__________________________|
            |           Text           | # Program code
            |__________________________|
```
