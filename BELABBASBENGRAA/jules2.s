	.data		
argErreur:	# message d'erreur pour les arguments
	.string "Il faut 2 arguments !!"
nbLettreAlphabet:
	.quad 26
shift: # décalage
	.quad 0
sautDeLigne: # caractère de saut de ligne
	.string "\n"

	.text
	.global _start
_start:
	pop %r8			# R8 = argc
	cmp $3, %r8		# R8 != 3 ?
	jne affiche_argErreur	# si oui aller à affiche_argErreur
	pop %rcx		# sinon RCX = argv[0]
	pop %rcx		# RCX = argv[1]
	call atoi		# RAX = atoi(rcx)
	mov %rax, shift	# shift = RAX
	pop %rcx		# RCX = argv[2]
	xor %r9, %r9		# r9 = 0		

boucle:
	xor %rdx, %rdx		# RDX = 0
	xor %rax, %rax          # RAX = 0
	mov (%rcx,%r9,1), %al	# AL = RCX[r9]
	test %al, %al		# AL = 0 ?
	jz fin			# si oui aller à fin
	sub $97, %rax		# sinon RAX -= 97 
	add shift, %rax	# RAX += shift
	divq nbLettreAlphabet		# RAX = RAX/nbLettreAlphabet et RDX = RAX%nbLettreAlphabet
	mov %rdx, %rax		# RAX = RDX
	add $97, %rax		# RAX += 97
	call affiche_char	# affiche le caractère stocké dans rax
	inc %r9		# r9 ++
	jmp boucle		# saut vers boucle

affiche_argErreur:			# affiche le message d'argErreur
	mov $argErreur, %rsi	# RSI = &argErreur
	call affiche_chaine			# appel de la fonction affiche_chaine

fin:				# affichage d'un saut de ligne et exit
	mov $sautDeLigne, %rsi		# RSI = &sautDeLigne (etiquette)
	call affiche_chaine			# appel de la fonction affiche_chaine
	mov $60, %rax		# RAX = 60
	xor %rdi, %rdi		# RDI = 0
	syscall			# exit(0)
