CC = gcc
LD = gcc
CFLAGS = -std=c99 -Wall -Werror
LDFLAGS =
RM = /bin/rm -f
OBJS = main.o funcs.o utilities.o
EXECUTABLE = CG

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

utilities.o: header.h utilities.h utilities.c
	$(CC) $(CFLAGS) -c utilities.c

funcs.o: header.h funcs.h funcs.c
	$(CC) $(CFLAGS) -c funcs.c

main.o: main.c funcs.h header.h
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) $(EXECUTABLE) $(OBJS)
