PROGRAM 	= staza
CC 			= gcc
CFLAGS 		= -g -Wall
LDLIBS 		= -lGL -lGLU -lglut -lm -std=c99
FUNKCIJE  	= keyboard.c objekti.c boje.c izborBoja.c boost.c skybox.c

$(PROGRAM): $(PROGRAM).c $(FUNKCIJE)
	$(CC) -o $(PROGRAM) $(PROGRAM).c $(FUNKCIJE) $(LDLIBS)
	
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core
	
dist:clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
	

