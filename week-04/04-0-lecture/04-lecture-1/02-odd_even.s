main:
    la $a0, string0     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", x);
    syscall
    move $t0, $v0       # x in $t0

    rem $v0, $t0, 2     # if (x % 2 == 0) {
    bne $v0, 1, even
    beq $v0, 7, even
    b odd
even:
    la $a0, string1     # printf("Even\n");
    li $v0, 4
    syscall

    b end

odd:                    # else
    la $a0, string2     # printf("Odd\n");
    li $v0, 4
    syscall

end:
    jr $ra              # return

    .data
string0:
    .asciiz "Enter a number: "
string1:
    .asciiz "Even\n"
string2:
    .asciiz "Odd\n"