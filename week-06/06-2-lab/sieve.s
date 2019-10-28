################################################################################
#                                                                              #
#  Elicia Au Duong - z5260173                                                  #
#  sieve.s                                                                     #
#  -----                                                                       #
#  Sieve of Eratosthenes                                                       #
#  https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes                         #
#                                                                              #
################################################################################
main:

    li $t0, 0                       # int i = 0
loop1:
    bge $t0, 1000, part2            # while (i < 1000) {
    
    la $t1, prime                   #   start of prime array
    add $t2, $t1, $t0               #   increment index
    
    li $t3, 1                       #   x = 1
    sb $t3, ($t2)                   #   prime[i] = x (i.e. prime[i] = 1)
    
    add $t0, $t0, 1                 #   i++
    
    j loop1                         # }
    
part2:    
    li $t0, 2                       # i = 2
    
loop2:
    bge $t0, 1000, end              # while (i < 1000) {
    
    la $t1, prime                   #   start of prime array
    add $t2, $t1, $t0               #   increment index
 
ifprime:                
    lb $t3, ($t2)                   #   load prime[i]
    bne $t3, 1, ifprimen            #   if (prime[i]) {
    
    move $a0, $t0                   #     printf("%d", i)
    li $v0, 1
    syscall
    
    li   $a0, '\n'                  #     printf("%c", '\n');
    li   $v0, 11
    syscall
    
    mul $t4, $t0, 2                 #     int j = 2 * i
    
loop3:
    bge $t4, 1000, ifprimen         #     while (j < 1000) {
    
    la $t1, prime                   #       start of prime array
    add $t2, $t1, $t4               #       increment j index
    
    li $t5, 0                       #       x = 0    
    sb $t5, ($t2)                   #       prime[j] = x (i.e. prime[j] = 0)
    add $t4, $t4, $t0               #       j++
    
    j loop3                         #     }
    
    
ifprimen:                           #   }
    add $t0, $t0, 1                 #   i++
    
    j loop2                         # }


end:
    li $v0, 0                       # return 0
    jr $31

.data
prime:
    .space 1000