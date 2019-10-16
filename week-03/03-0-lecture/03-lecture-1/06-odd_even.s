main:
    la $a0, string0     # printf("Enter a number: ");
    li $v0, 4
    syscall

    li $v0, 5           # scanf("%d", x);
    syscall

    and $v0, $v0, 1     # if (x & 1 == 0) {
    beq $v0, 1, odd

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