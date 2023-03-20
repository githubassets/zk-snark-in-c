CC  = gcc
# CFLAGS  = -fsanitize=address -fno-omit-frame-pointer -std=gnu11 -Wall -Wextra -Wpedantic -O0 -g -ftrapv -Wno-discarded-qualifiers
# LFLAGS  = -fsanitize=address -fno-omit-frame-pointer -lm -lrt -lpbc -lgmp -lgsl -lcblas -L/usr/local/lib/
CFLAGS  = -fno-omit-frame-pointer -std=gnu11 -Wall -Wextra -Wpedantic -O0 -g -ftrapv -Wno-discarded-qualifiers -Wno-missing-braces
LFLAGS  = -fno-omit-frame-pointer -lm -lrt -lpbc -lgmp -lgsl -lcblas -L/usr/local/lib/

OBJ := obj/
SOURCES := $(wildcard *.c)
OBJECTS := $(patsubst %.c, $(OBJ)%.o, $(SOURCES))

all: dir install

reinstall: clean install

install: $(OBJECTS)
	    @$(CC) $^ -o main $(LFLAGS)
	@./main

dir:
	@mkdir -p $(OBJ)

%.o: ../%.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@$(CC) $(CFLAGS) -MM $< -o $*.d

clean:  
	@\rm -f $(OBJECTS)
	@\rm -f $(OBJ)*.d
	@\rm -f main

-include $(OBJECTS:.o=.d)
