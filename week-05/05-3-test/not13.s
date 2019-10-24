#  Print the numbers between two integers excluding 13
#  Test 05 - 24 October 2019
#  Elicia AU DUONG - z5260173

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    addi $t2, $t0, 1    #   int i = x + 1
loop:
    bge $t2, $t1, end   #   while (i < y) {
    beq $t2, 13, incr   #       if (i != 13) {
    move $a0, $t2       #           printf("%d", i);
    li $v0, 1
    syscall
    li   $a0, '\n'      #           printf("%c", '\n');
    li   $v0, 11
    syscall             #       }
incr:
    add $t2, $t2, 1     #       i = i + 1
    
    j loop              #   }

end:

    li $v0, 0           # return 0
    jr $31