EXAMPLES = pip
CC = gcc
CFLAGS = -Wall -Wextra -O2

.PHONY: all clean

all: $(EXAMPLES)

pip: pip.c
	$(CC) $(CFLAGS) -o $@ $<
	@echo "Compiled $(<). Generated $(@) binary."

clean:
	rm -f $(EXAMPLES)

