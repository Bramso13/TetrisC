	.data			# Verification des caractères
point:				
	.string "."

	.text
	.global verification
verification:
verifMinuscule:
	cmp $97, %rax		# RAX < 97 ?
	jl verifMajuscule	# si oui alors aller a verifMajuscule
	cmp $122, %rax		# sinon RAX > 122 ?
	jg verifCharSpeciaux	# si oui alors aller a verifCharSpeciaux
	xor %r14, %r14		# r14 = 0
	ret $0			# Retour vers le programme appelant

verifMajuscule:
	cmp $65, %rax		# RAX < 65 ?
	jl verifCharSpeciaux	# si oui alors aller a verifCharSpeciaux
	cmp $90, %rax		# RAX > 90 ?
	jg verifCharSpeciaux	# si oui alors aller à verifCharSpeciaux
	add $32, %rax		# RAX += 32 (COnversion en minuscule)
	xor %r14, %r14		# r14 = 0 
	ret $0			# Retour vers le programme appelant

verifCharSpeciaux:
	test %r14, %r14		# r14 = 0 ?
	jz affichePoint	# si oui alors aller à affichePoint
	inc %r12		# R12 ++ sans afficher le point car déjà afficher
	mov $1, %r14		# r14 = 1
	ret $0			# Retour vers le programme appelant
	
affichePoint:			# affichage du point
	mov $1, %rax
	mov $1, %rdi
	mov $1, %rbx
	mov $point, %rsi	# RSI = &point (etiquette)
	call affiche_chaine	# appel de la fonction affiche_chaine
	mov $1, %r14		# r14 = 1
	inc %r12		# R12 ++
	ret $0			# Retour vers le programme appelant
