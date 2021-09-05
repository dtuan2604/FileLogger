CC = gcc
CFLAGS = -Wall
DEPS = drive.c
OBJ = driver.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

driver: $(OBJ)
	gcc $(CFLAGS) -lm -o $@ $^
