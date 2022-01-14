; this is pseudo code

_start:
    mov r1, 0       ; i
    mov r2, 1       ; increment by
    mov r3, 10      ; max val

jump:
    add r1, r2      ; add r1 and r2
    lar r1          ; load accumulator to r1

    jne r1,r2,jump  ; jump if r1 != r2

    hlt             ; halt
