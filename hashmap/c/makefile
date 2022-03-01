EXEC  = "hashexec"
ARCH := $(shell uname -p)
# Modify if needed.
ifeq ($(ARCH), X86_64)
	CC = gcc
else
	CC = clang
endif

SRC  = $(wildcard *.c)
OBJ  = $(SRC:.c=.o)
LDFL = #libs like math...
# Replace O3 with -g to debug.
CFLAGS = -c			\
	     -g			\
	     -W			\
		 -Wall		\
	     -pedantic

all: $(EXEC)

${EXEC}: $(OBJ)
	$(CC) -o $@ $^ $(LDFL)

%.o: %.c
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
