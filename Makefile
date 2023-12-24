CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INC = $(wildcard *.h)

all : bnav

%.o : %.c $(INC)
	$(CC) -c $< -o $@

bnav : $(OBJ)
	$(CC) $^ -o $@

clean :
	rm -f *.o 
	rm -f bnav