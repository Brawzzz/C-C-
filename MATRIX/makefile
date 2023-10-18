CC = gcc
SRC = $(wilcard *.c)
OBJ = $(SRC :.c = .o)

all : main

Matrix.o : Matrix.c
	$(CC) -c $< -o $@

main.o : main.c
	$(CC) -c $< -o $@

main : main.o Matrix.o -lm
	$(CC) $^ -o $@