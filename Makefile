CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all : bnav

%.o : %.c 
	$(CC) -c $< -o $@

bnav : $(OBJ)
	$(CC) $^ -o $@

clean :
	rm -f *.o 
	rm -f bnav