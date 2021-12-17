        .data			
base:				# le module atoi qui transforme la
        .quad 10		# chaine  pointée  par  RCX  en sa 
	.text			# valeur entière réelle  et met le 
	.global atoi            # resultat  dans le  registre  RAX 
atoi:
        xor %rax, %rax 		# RAX = 0
        xor %r10, %r10   	# R10 = 0
	xor %rbx, %rbx		# RBX = 0
tant_que:
        movb (%rcx, %r10), %bl 	# BL = RCX[R10]
        test %bl,%bl    	# BL = 0 ?
        jz fin          	# si vrai alors fini
        subb $48, %bl   	# sinon BL -= 48
        mulq base       	# RAX *= 10
        add %rbx, %rax  	# RAX += RBX
        inc %r10		# R10 ++
        jmp tant_que		# saut vers tant_que (boucle)
fin:
	ret $0			# retour vers programme principal
