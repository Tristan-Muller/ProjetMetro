all : main.o



clean : 
	rm *.o main

Do : main.o 
	./main


Do_debugg : debugg.o
	gdb main

debugg.o : abr.o aqr.o ligne.o liste.o truc.o
	gcc -g -o main main.c



main.o : abr.o aqr.o ligne.o liste.o truc.o
	gcc -Wall -o main main.c



abr.o : abr.c abr_type.h liste.h
	gcc -c abr.c

aqr.o : aqr.c aqrtopo.h coord.h ligne.h ligne.c
	gcc -c aqr.c

ligne.o : ligne.c ligne.h coord.h station.h liste.h
	gcc -c ligne.c

liste.o : liste.c liste.h abr_type.h coord.h station.h truc.h truc.o
	gcc -c liste.c

truc.o : truc.c truc.h coord.h station.h
	gcc -c truc.c
