    .text
.global affiche_chaine

affiche_chaine:
    xor %rdx, %rdx
    mov %rsi, %rbx
boucle:
    movb (%rbx), %al
    test %al, %al
    jz fin
    inc %rdx
    inc %rbx
    jmp boucle
fin:
    mov $1, %rax
    mov $1, %rdi
    syscall
    ret
