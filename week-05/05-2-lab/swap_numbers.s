################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  swap_numbers.s                                                              #
#  -----                                                                       #
#  Read 10 numbers into an array                                               #
#  Swap any pairs of of number which are out of order                          #
#  Then print the 10 numbers                                                   #
#                                                                              #
#  i in register $t0                                                           #
#  registers $t1 - $t3 used to hold temporary results                          #
#                                                                              #
################################################################################

main:

    li $t0, 0               # i = 0
loop0:
    bge $t0, 10, end0       # while (i < 10) {

    li $v0, 5               #   scanf("%d", &numbers[i]);
    syscall                 #

    mul $t1, $t0, 4         #   calculate &numbers[i]
    la $t2, numbers         #
    add $t3, $t1, $t2       #
    sw $v0, ($t3)           #   store entered number in array

    add $t0, $t0, 1         #   i++;
    b loop0                 # }
end0:


    li $t0, 1               # i = 1;
loop2:
    bge $t0, 10, end2       # while (i < 10) {
    mul $t1, $t0, 4         #   calculate &numbers[i]
    la $t2, numbers         #
    add $t3, $t1, $t2       #    
    lw $t4, ($t3)           #   int x = numbers[i]

    sub $t5, $t0, 1         #   j = i - 1
    mul $t1, $t5, 4         #   calculate &numbers[i - 1]
    la $t2, numbers         #
    add $t6, $t1, $t2       #
    lw $t7, ($t6)           #   int y = numbers[i - 1]

    bge $t4, $t7, plus      #   if (x < y) {

    sw $t7, ($t3)           #     numbers[i] = y;
    
    sw $t4, ($t6)           #     numbers[i - 1] = x;
                            #   }
plus:
    add $t0, $t0, 1         #   i++;
    j loop2                 # }
    
end2:
    li $t0, 0                   # i = 0
loop1:
    bge $t0, 10, end1       # while (i < 10) {

    mul $t1, $t0, 4         #   calculate &numbers[i]
    la $t2, numbers         #
    add $t3, $t1, $t2       #
    lw $a0, ($t3)           #   load numbers[i] into $a0
    li $v0, 1               #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'          #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1         #   i++
    b loop1                 # }
end1:

    jr $31                  # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};
