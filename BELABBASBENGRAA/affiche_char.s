	.data	# Affichage d'un caractère 		
tableau:				
	.quad 0		
	.text			
	.global affiche_char	
affiche_char:
	xor %rbx, %rbx		# RBX = 0
	mov $tableau, %rsi	# RSI = &tableau
	mov %rax, (%rsi,%rbx,8) # RSI[RBX] = RAX
fin:
	push %rcx		# j'empile le contenu du registre RCX
	mov $1, %rax		# RAX = 1
	mov $1, %rdi		# RDI = 1
	mov $1, %rdx		# RDX = 1
	syscall		# write(stdout, rsi, 1);
	pop %rcx		# je dépile le contenu du registre RCX dans rcx
	ret $0			# retour vers le programme principal
