CC = gcc

.PHONY: clean

all: needleman_wunsch

needleman_wunsch: needleman_wunsch.c
	$(CC) -o $@ $<

clean:
	rm -f needleman_wunsch *.o .*.c.swm .*.c.swn .*.h.swn .*.h.swo .*.h.swp .*.c.swp
