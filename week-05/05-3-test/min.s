#  Print the minimum of two integers
#  Test 05 - 24 October 2019
#  Elicia AU DUONG - z5260173

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $v0, 5           #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bge $t0, $t1, yprint
    move $a0, $t0          #   printf("%d\n", x);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
    
    j end
    
yprint:
    move $a0, $t1       #   printf("%d", y);
    li $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

end:

    li $v0, 0           # return 0
    jr $31
    