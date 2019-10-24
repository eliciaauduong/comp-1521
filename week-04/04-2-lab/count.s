################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  count.s                                                                     #
#  -----                                                                       #
#  Read a number n and print the integers 1..n one per line                    #
#                                                                              #
################################################################################

main:                           # int main(void)
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall

    move $t0, $v0               # store the number in t0
        
    li   $t1, 1                 # start loop counter i at 1
      
loop:                           # while loop from i to n
    
    bgt  $t1, $t0, end          # if i > num goto end
    
    move $a0, $t1               # print i
    li  $v0, 1
    syscall
    
    li   $a0, '\n'              # print \n
    li   $v0, 11
    syscall
    
    add $t1, $t1, 1             # increment by 1
   
    j loop                      # goto loop
        
end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "