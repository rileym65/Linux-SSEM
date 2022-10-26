PROJECT = asm
CC = gcc
DEFS =
INCDIR =
INCS =
LIBDIR =
LIBS = 
DEFS = 
OBJS = \
	main.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.cpp.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm $(PROJECT)
	-rm *.o

main.o:            main.c

