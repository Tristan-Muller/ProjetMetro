all : abr.o aqr.o ligne.o liste.o truc.o


clean : 
	rm *.o


abr.o : abr.c abr_type.h
	gcc -c abr.c

aqr.o : aqr.c aqrtopo.h
	gcc -c aqr.c

ligne.o : ligne.c ligne.h
	gcc -c ligne.c

liste.o : liste.c liste.h
	gcc -c liste.c

truc.o : truc.c truc.h
	gcc -c truc.c
