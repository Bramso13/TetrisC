	.data
err:				
	.string "Il faut 2 arguments !!"
lettreAlphabet:			
	.quad 26
sautdeligne:				
	.string "\n"
	
	.text
	.global _start
_start:
	pop %r8			# R8 = argc
	cmp $3, %r8		# R8 != 3 ?
	jne affiche_err	# si oui alors aller a err
	pop %r9			# sinon R9 = argv[0]
	pop %r9			# R9 = argv[1]
	pop %r10		# R10 = argv[2]
	xor %r12, %r12		# R12 = 0
	xor %r13, %r13		# R13 = 0
	xor %r14, %r14		# R14 = 0
	
boucle:
	xor %rdx, %rdx		# RDX = 0
	mov (%r10, %r12), %al	# AL = R10[R12]
	test %al, %al		# AL = 0 ?
	jz fin			# si oui alors aller a fin
	mov (%r9, %r13), %bl	# BL = R9[R13]
	test %bl, %bl		# BL = 0 ?
	jz initCle	# si oui alors aller a initcle

continu:
	call verification	# verifie le caractere 
	test %r14, %r14		# R14 != 0 ?
	jnz boucle
	sub $97, %rbx		
	add %rax, %rbx
	cmp $122, %rbx
	jg plusgrand
	cmp $122, %rbx
	jle pluspetit
	
initCle:		# reinitialise la clé
	xor %r13, %r13		# R13 = 0
	mov (%r9, %r13), %bl	# BL = R9[R13]
	jmp continu		# saaut vers continu

affiche_err:			# affiche le message d'err 
	mov $err, %rsi	# RSI = &err
	call affiche_chaine # appel de la fonction affiche_chaine

plusgrand:
	sub $123, %rbx
	mov %rbx, %rax
	add $97, %rax
	call affiche_char
	inc %r12		# R12 ++
	inc %r13		# R13 ++
	jmp boucle		# saut vers boucle

pluspetit:
	mov %rbx, %rax
	call affiche_char
	inc %r12		# R12 ++
	inc %r13		# R13 ++
	jmp boucle		# saut vers boucle

fin:				# affichage d'un sautdeligne de ligne et fin
	mov $sautdeligne, %rsi		# RSI = &sautdeligne
	call affiche_chaine			# appel de la fonction affiche_chaine
	
	mov $60, %rax		# RAX = 60
	xor %rdi, %rdi		# RDI = 0
	syscall			# exit(0)
	ret			# fin du programme
