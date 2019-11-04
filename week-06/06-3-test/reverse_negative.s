#  Read numbers into an array until a negative number is entered
#  then print the numbers in reverse order
#  i in register $t0
#  Registers $t1, $t2 & $t3 used to hold temporary results
#  Test 06 - 30 October 2019
#  Elicia AU DUONG - z5260173


main:
    li $t0, 0               # i = 0
loop0:
    bge $t0, 1000, loop1    # while (i < 1000) {

    li $v0, 5               #   scanf("%d", &x);
    syscall                 #
    
    bge $v0, 0, loop0n      #   if (x < 0) {
    j loop1                 #     break

loop0n:                     #   } else {
    mul $t1, $t0, 4         #     calculate &numbers[i]
    la $t2, numbers         #
    add $t3, $t1, $t2       #
    sw $v0, ($t3)           #     numbers[i] = x
                            #   }
    add $t0, $t0, 1         #   i++;
    b loop0                 # }
    
loop1:
    ble $t0, 0, end         # while (i > 0) {
    sub $t0, $t0, 1         #   i--
    
    mul $t1, $t0, 4         #   calculate &numbers[i]
    la $t2, numbers         #
    add $t3, $t1, $t2       #
    lw $t4, ($t3)           #   load numbers[i]
    move $a0, $t4           #   printf("%d", numbers[i])
    li $v0, 1
    syscall
    li $a0, '\n'            #   printf('\n')
    li $v0, 11
    syscall
    j loop1                 # }
    
end:
    li $v0, 0               # return 0
    jr $31                  #

.data
numbers:
    .space 4000