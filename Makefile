
### BUT PAR DEFAUT ###

but : snake

### VARIABLES ### 
OFILES = affichage.o \
		 vitesse.o \
		 deplacer.o \
		 main.o

CC = gcc
CFLAGS = -Wall -ansi -pedantic -g

### REGLES POUR COMPILER LE PROGRAMME ###

affichage.o : affichage.h
vitesse.o : vitesse.h 
deplacer.o : deplacer.h affichage.h
main.o : affichage.h deplacer.h vitesse.h

snake : $(OFILES)
	$(CC) $(CFLAGS) -o  snake $(OFILES) -lgraph

### REGLE POUR  EXECUTER LE PROGRAMME ### 

run :snake
	./snake

### REGLER POUR NETTOYER LES FICHIER GENERES LORS DE LA COMPILATION ###

clean :
	-rm -f $(OFILES) snake

.PHONY : but clean