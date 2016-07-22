# if there is a clock skew detected, run:
# find /your/dir -type f -exec touch {} +

CC = gcc
C_STANDARD = -std=c99
CFLAGS = -Wall -ansi ${C_STANDARD}
TITLE = compress

$(TITLE).x: $(TITLE).o
	$(CC) $(CFLAGS) $^ -o $@

$(TITLE).o: $(TITLE).c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o $(TITLE).x
