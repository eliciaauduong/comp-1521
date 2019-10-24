#  Print a square of asterisks
#  Test 05 - 24 October 2019
#  Elicia AU DUONG - z5260173

main:
    li $v0, 5           #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li $t1, 0           #   int i = 0;
iloop:
    bge $t1, $t0, end   #   while (i < x) {

    li $t2, 0           #       int j = 0;

jloop:    
    bge $t2, $t0, iplus #       while (j < x) {
    
    li $a0, '*'         #           printf("*");
    li $v0, 11
    syscall

    add $t2, $t2, 1     #           j = j + 1;
    
    j jloop             #       }
    
iplus:
    add $t1, $t1, 1     #       i = i + 1
    
    li   $a0, '\n'      #       printf("%c", '\n');
    li   $v0, 11
    syscall
    
    j iloop             #   }

end:

    li $v0, 0           # return 0
    jr $31