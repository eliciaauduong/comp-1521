main:
    li $t0, 1

    sb $t0, a            # will succeed because no alignment needed
    sh $t0, a            # will fail a because is not aligned on 2-byte boundary
    sw $t0, a            # will fail a because is not aligned on 3-byte boundary

    sh $t0, b            # will succeeed because b is aligned on 2-byte boundary
    sw $t0, b            # will fail b because is not aligned on a 4-byte boundary

    sh $t0, c            # will succeeed because c is aligned on 2-byte boundary
    sw $t0, c            # will fail d because is not aligned on a 4-byte boundary

    sh $t0, d            # will succeeed because d is aligned on 2-byte boundary
    sw $t0, d            # will succeeed because d is  aligned on a 4-byte boundary

    sw $t0, e            # will succeeed because e is aligned on a 4-byte boundary

    sw $t0, f            # will succeeed because f is aligned on a 4-byte boundary

    jr   $ra             # return

    .data     # data will be aligned on a 4-byte boundary
              # most likely on at least a 128-byte boundary
              # but safer to just add a .align directive
    .align 2
    .space 1
a:
    .space 1
b:
    .space 4
c:
    .space 2
d:
    .space 4
    .space 1
    .align 2 # ensure e is on a 4 (2**2) byte boundary
e:
    .space 4
    .space 1
f:
    .word 0  # word directive automaticatically aligns on 4 byte boundary