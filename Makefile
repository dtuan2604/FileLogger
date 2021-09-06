CC = gcc
CFLAGS = -Wall
DEPS = loglib.c drive.c
OBJ = loglib.o driver.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

driver: $(OBJ)
	gcc $(CFLAGS) -lm -o $@ $^
clean:
	rm *.o 
