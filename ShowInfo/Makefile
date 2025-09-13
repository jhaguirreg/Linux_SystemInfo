# Código para compilar directamente (con make).

CC=gcc # gcc será nuestro compilador 
CFLAGS=-Wall -lncurses # Opciones adicionales: Wall- Detectar errores. lncurses- TUI.

all: ShowInfo # Nombre del compilador 

ShowInfo: src/main.c src/cpu.c src/mem.c # Archivos del programa.
	$(CC) src/main.c src/cpu.c src/mem.c -o ShowInfo $(CFLAGS) # Compilar.

clean:
	rm -f ShowInfo # Para limpiar la compilación (con make clean).
