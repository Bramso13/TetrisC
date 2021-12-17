as = as
option = -a `--gstabs`
ld = ld

cesar : affiche_chaine.o affiche_char.o atoi.o jules2.o
	$(ld) affiche_chaine.o affiche_char.o atoi.o jules2.o -o cesar

vigenere : affiche_chaine.o affiche_char.o verification.o vigenere.o
	$(ld) affiche_chaine.o affiche_char.o verification.o vigenere.o -o vigenere

affiche_chaine.o : affiche_chaine.s
	$(as) $(option) affiche_chaine.s -o affiche_chaine.o

verification.o : verification.s
	$(as) $(option) verification.s -o verification.o

affiche_char.o : affiche_char.s
	$(as) $(option) affiche_char.s -o affiche_char.o

atoi.o : atoi.s
	$(as) $(option) atoi.s -o atoi.o

vigenere.o : vigenere.s
	$(as) $(option) vigenere.s -o vigenere.o

jules2.o : jules2.s
	$(as) $(option) jules2.s -o jules2.o

clean:
	rm -f *.o *~ cesar vigenere