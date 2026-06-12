all: gol

RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

gol: main.o gol_grid.o
	gcc bin/gol_grid.o src/main.c -o bin/gol $(RAYLIB)

main.o:
	gcc -c src/main.c -o bin/main.o

gol_grid.o:
	gcc -c src/gol_grid.c -o bin/gol_grid.o

clean:
	rm -rf bin/*
