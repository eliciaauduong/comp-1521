#  Read a line and print whether it is a palindrome
#  Test 07 - 06 November 2019
#  Elicia AU DUONG - z5260173

main:
    la   $a0, str0              # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8                 # fgets(buffer, 256, stdin)
    syscall                     #

    li $t0, 0                   # int i = 0;
loop:
    la $t1, line                # calculate the adress of line[i]
    add $t2, $t1, $t0           #
    lb $t3, ($t2)               # get the number stored in line[i]
    beq $t3, 0, next            # while (line[i] != 0) {
    add $t0, $t0, 1             #   i++;
    j loop                      # }
    
next:
    li $t4, 0                   # int j = 0;
    sub $t5, $t0, 2             # int k = i - 2;

loop1:
    bge $t4, $t5, palin         # while (j < k) {
    la $t1, line                #   calculate the adress of line[j]
    add $t2, $t1, $t4           #
    lb $t3, ($t2)               #   get the number stored in line[j]
    la $t1, line                #   calculate the adress of line[k]
    add $t2, $t1, $t5           #
    lb $t6, ($t2)               #   get the number stored in line[k]
    
    beq $t3, $t6, loop1n        #   if (line[j] != line[k]) {
    
    la   $a0, not_palindrome    #     printf("not palindrome\n");
    li   $v0, 4
    syscall
    
    li   $v0, 0                 #     return 0
    jr   $31

loop1n:                         #   }
    add $t4, $t4, 1             #   j++;
    sub $t5, $t5, 1             #   k--;
    j loop1                     # }
    
palin: 

    la   $a0, palindrome        # printf("palindrome\n");
    li   $v0, 4
    syscall
    
    li   $v0, 0                 # return 0
    jr   $31


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256
