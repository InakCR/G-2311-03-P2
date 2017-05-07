#Carpetas make -f
DOC = ./doc/
LIB = ./lib/
MAN = ./man/
OBJ = ./obj/
SRCLIB = ./srclib/
SRC = ./src/
DIRS = obj lib
GROUP = G-2311-03-P2
#Compilador
CC = gcc -pthread
#Librerias
LDFLAGS = -lm
CCLIBS = -lircinterface -lircredes -lirctad
CCLAGS =  -rdynamic
CCSOUND = -lsoundredes -lpulse -lpulse-simple
FLAGS = `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
FLAGSE = `pkg-config --libs gtk+-3.0`
FLAGSC = `pkg-config --cflags gtk+-3.0`
#Ficheros
EXEC = cliente
SOURCE_FILES =

all: $(EXEC)

$(EXEC): $(GROUP)xchat2.o
			$(CC) $^ -o $@ $(CCLIBS) $(FLAGSE) $(CCLAGS) $(CCSOUND)

$(GROUP)xchat2.o: $(GROUP)xchat2.c
			$(CC) $(CCLAGS) $(CCSOUND) $(FLAGSC) -c -o $@ $^

clean:
		rm -f *.o *.gch $(GROUP).tar.gz $(EXEC)

dox:
		doxygen Doxyfile

tar:
		@ echo "Comprimiendo el archivo"
		tar --exclude .git -czvf $(GROUP).tar.gz ../$(GROUP) --exclude $(GROUP).tar.gz
		@ echo "Archivo comprimido ..."
