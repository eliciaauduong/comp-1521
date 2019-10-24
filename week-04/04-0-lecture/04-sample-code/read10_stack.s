in:
    sub  $tp, $tp, 40    # move stack pointer down to make room
                         # to store array numbers on stack
    li   $t0, 0          # i = 0

loop0:
    bge  $t0, 10, end0   # while (i < 10) {
    la   $a0, string0    #  printf("Enter a number: ");
    li   $v0, 4
    syscall

    li   $v0, 5         #  scanf("%d", &numbers[i]);
    syscall             #

    mul  $t1, $t0, 4    #  calculate &numbers[i]
    add  $t1, $t1, $tp  #
    sw   $v0, ($t1)     #  store entered number in array

    add  $t0, $t0, 1    #  i++;
    b    loop0          # }
end0:

    li   $t0, 0         # i = 0
loop1:
    bge  $t0, 10, end1  # while (i < 10) {

    mul  $t1, $t0, 4
    add  $t1, $t1, $t0  #   calculate &numbers[i]
    lw   $a0, ($t1)     #   load numbers[i] into $a0
    li   $v0, 1         #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add  $t0, $t0, 1    #   i++
    b    loop1          # }
end1:

    add  $tp, $tp, 40   # move stack pointer back up to what it was when main called
    li   $v0, 0         # return 0 from function main
    jr   $ra            #

.data
string0:
    .asciiz "Enter a number: "