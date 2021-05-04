# paths
INCLUDE =../include
MODULES=../modules

# compiler
CC = g++ 

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CPPFLAGS = -std=c++11 -Wall  -g3 -I$(INCLUDE)
LDFLAGS = -lm

# Αρχεία .o
OBJS =   main.o $(MODULES)/Grid.o $(MODULES)/Inventory.o $(MODULES)/Living.o $(MODULES)/Squares.o $(MODULES)/Randomness.o

# Το εκτελέσιμο πρόγραμμα
EXEC = main


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)


clean:
	rm -f $(OBJS) $(EXEC)

run: $(EXEC)
	./$(EXEC) $(ARGS)

valgrind: run
	valgrind ./$(EXEC)