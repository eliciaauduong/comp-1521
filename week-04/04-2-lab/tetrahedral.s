################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  tetrahedral.s                                                               #
#  -----                                                                       #
#  Read a number n and print the first n tetrahedral numbers                   #
#  https://en.wikipedia.org/wiki/Tetrahedral_number                            #
#                                                                              #
################################################################################

main:                       # int main(void) {

    la $a0, prompt          # printf("Enter how many: ");
    li $v0, 4
    syscall
    
    li $v0, 5               # scanf("%d", number);
    syscall

    move $t0, $v0           # store how many in t0

    li $t1, 1               # store 1 in n

nloop:
    bgt $t1, $t0, end       # while (n <= how_many) 
    
    li $t2, 0               # total = 0
    li $t3, 1               # j = 1

    j jloop                 # go into the next while loop
    
jloop:
    bgt $t3, $t1, jloopn    # while (j <= n)
    li $t4, 1               # i = 1;
    
    j iloop                 # go into the next while loop
    
iloop:    
    bgt $t4, $t3, iloopn    # while (i <= j) {
    add $t2, $t2, $t4       # total = total + i;
    add $t4, $t4, 1         # i = i + 1;
    
    j iloop                 # }

iloopn:
    add $t3, $t3, 1         # j = j + 1;
    
    j jloop                 # }

jloopn:                        
    move $a0, $t2           # printf("%d", total);
    li  $v0, 1
    syscall             
                       
    li   $a0, '\n'          # printf("%c", '\n');
    li   $v0, 11
    syscall
     
    add $t1, $t1, 1         # n = n + 1;
    
    j nloop                 # }

    li $a0, 42              # printf("%d", 42);
    li   $v0, 1
    syscall

end:
    jr   $ra            # return

    .data
prompt:
    .asciiz "Enter how many: "