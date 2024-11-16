# jpeg colorswap Makefile

DEFINES =
DEBUG = -g3 -O0
WERROR =
WERROR = -Werror
CFLAGS = -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
-Wdeclaration-after-statement -Wextra -Werror -Wpedantic \
$(WERROR) $(DEBUG) $(DEFINES)

CC = gcc $(CFLAGS)
PROG = colorswap

all: $(PROG)

$(PROG): colorswap.o
	$(CC) -o $@ $^ -ljpeg -lm

colorswap.o: colorswap.c
	$(CC) -c $^

clean cls:
	rm -f *.o colorswap *~\#*

# local version control
git checkin chicken push:
	if [ ! -d .git ]; then git init; fi
	git add *.[ch] ?akefile
	git commit -m "git checkin comment"
