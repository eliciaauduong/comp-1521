################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  seven_eleven.s                                                              #
#  -----                                                                       #
#  Read a number and print positive multiples of 7 or 11 < n                   #
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
    
    bge  $t1, $t0, end          # if i >= num goto end
    
    rem $v0, $t1, 7             # if divisble by 7 
    beq $v0, $0, then           # goto then (i.e. print the number)

    rem $v0, $t1, 11            # if divisble by 11
    beq $v0, $0, then           # goto then (i.e. print the number)
    
next:      
    add $t1, $t1, 1             # increment by 1
   
    j loop                      # goto loop

then:
    move $a0, $t1               # print i
    li  $v0, 1
    syscall
        
    li   $a0, '\n'              # print \n
    li   $v0, 11
    syscall
    
    j next                      # return back to the loop
    
end:
    jr  $ra                     # return

    .data
prompt:
    .asciiz "Enter a number: "