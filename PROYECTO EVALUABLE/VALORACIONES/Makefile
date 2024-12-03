CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++11
DEPS = alojamiento.hpp alojamientos.hpp utilidades.hpp valoracion.hpp valoraciones.hpp palabras.hpp
OBJ = alojamiento.o alojamientos.o utilidades.o valoracion.o valoraciones.o palabras.o

ifeq ($(OS),Windows_NT) 
RM=del /Q /F
EXT=.exe
else
RM=rm -rf
EXT=
endif

all: test_valoraciones test_palabras main_valoraciones

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_valoraciones: valoracion.o valoraciones.o utilidades.o test_valoraciones.o palabras.o
	$(CC) -o $@ $^ $(CFLAGS)

test_palabras: utilidades.o test_palabras.o palabras.o
	$(CC) -o $@ $^ $(CFLAGS)

main_valoraciones: $(OBJ) valoracion.o valoraciones.o utilidades.o main_valoraciones.o palabras.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	-$(RM) test_valoraciones$(EXT) test_palabras$(EXT) main_valoraciones$(EXT) *.o

main: main_valoraciones
	./main_valoraciones

test: test_valoraciones
	./test_valoraciones

.PHONY: clean all test main

