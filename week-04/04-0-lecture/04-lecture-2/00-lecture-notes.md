# Lecture 2 Notes
Thursday October 10, 2019

## Functions
Register usage conventions when `f()` calls `g()`:
- caller saves registers (saved by `f()`)
    - `f()` tells `g()` "If there is anything I want to preserve in the registers, I have already saved it before calling you"
    - `g()` tells `f()` "Don't assume that these registers will be unchanged when I return to you"
    - e.g. `$t0 .. $t9`, `$a0 .. $a3`, `$ra`
- callee saved registers (saved by `g()`)
    - `f()` tells `g()` "I assume the values of these registers will be unchanged when you return"
    - `g()` tells `f()` "If I need to use these registers, I will save them first and restore them before returning"
    - e.g. `$s0 .. $s7`, `$sp`, `$fp`

---

### Aside: Branch Delay Slots
Most architectures are "pipelined" to improve eﬃciency.
- Next instruction(s) can start before previous one(s) ﬁnish 
- MIPS has a two-stage pipeline: fetch, and execute 

What if a branching instruction (e.g. jal) is executed?
- Next fetch happens before branch executes ⇒ next instruction is loaded.
- So, either ’stall’ the pipeline until it completes (slow!) 
- ... or run the next instruction anyway, in a "branch-delay" slot 

On classical MIPS, the next instruction is executed before the branch completes

To avoid potential problems, use nop immediately after branch A problem scenario, and its solution (branch delay slot):

``` MIPS
# Implementation of print(compute(42)) 

li $a0, 42              li $a0, 42 
jal compute             jal compute 
move $a0, $v0           nop 
jal print               move $a0,$v0 
                        jal print 
```

Since SPIM is not pipelined (by default), the nop is not required


### Aside: Why do we need both $fp and $sp?
During execution of a function 
- `$sp` can change (e.g. pushing params, adding local vars) 
- May need to reference local vars on the stack 
- Useful if they can be deﬁned by an oﬀset relative to ﬁxed point 
- `$fp` provides a ﬁxed point during function code execution 

``` C
int f(int x) { 
    int y = 0;                      // y created in prologue 
    for (int i = 0; i < x; i++) {   // i created in for-loop 
        y += i;                     // which changes $sp 
    } 
    return y; 
}
```

It is possible to only use `$sp`, which frees up `$fp` to become `$s8`. But at the cost of lots of extra work for us in keeping track of stack layout.

---
