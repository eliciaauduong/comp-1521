################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  bad_pun.s                                                                   #
#  -----                                                                       #
#  Print "I MIPS you!" in MIPS (from i_love_mips.s in lecture)                 #
#                                                                              #
################################################################################
main:
    la   $a0, string  # get addr of string
    li   $v0, 4       # 4 is print string syscall
    syscall
    
    jr   $ra          # return

    .data # data in this segment is placed in the data segment of memory
string:
    .asciiz "I MIPS you!\n" # store a string in the data segment of memory