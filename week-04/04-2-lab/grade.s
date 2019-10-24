################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  grade.s                                                                     #
#  -----                                                                       #
#  Read a mark and print the corresponding UNSW grade                          #
#                                                                              #
################################################################################
main:
    la $a0, prompt          # printf("Enter a mark: ");
    li $v0, 4
    syscall

    li $v0, 5               # scanf("%d", mark);
    syscall
    
    blt $v0, 50, printfl    # if mark < 50 FL

    blt $v0, 65, printps    # if mark < 65 PS
    
    blt $v0, 75, printcr    # if mark < 75 CR
    
    blt $v0, 85, printdn    # if mark < 85 DN
    
    # if the mark is not less than 85
    # (skips all previous conditions)
    # mark must be >= 85 so HD
    # print HD
    la $a0, hd          
    li $v0, 4
    syscall
    
    j end

printfl:                    # print FL 
    la $a0, fl          
    li $v0, 4
    syscall
    j end

printps:                    # print PS
    la $a0, ps          
    li $v0, 4
    syscall
    j end
    
printcr:                    # print CR
    la $a0, cr          
    li $v0, 4
    syscall
    j end
    
printdn:                    # print DN 
    la $a0, dn          
    li $v0, 4
    syscall
    j end

end:
    jr $ra                  # return


    .data
prompt:
    .asciiz "Enter a mark: "
fl:
    .asciiz "FL\n"
ps:
    .asciiz "PS\n"
cr:
    .asciiz "CR\n"
dn:
    .asciiz "DN\n"
hd:
    .asciiz "HD\n"