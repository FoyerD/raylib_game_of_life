all: gol


gol: gol.c
	gcc gol.c -o bin/gol -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm -rf bin/*
