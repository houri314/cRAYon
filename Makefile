BUILDTYPE ?= Release
THEME ?= default
CC := gcc
INCLUDE := -I./include/
OPT ?= 0
EXT ?= .exe

C_SOURCE := $(wildcard src/*.c)
OBJ := $(C_SOURCE:.c=.o)

LIBS := -lraylib -lgdi32 -lwinmm -mwindows
INCLUDE := -I./include

ifeq ($(BUILDTYPE),Debug)
CFLAGS := -Og -g $(INCLUDE) $(LIBS)
else
CFLAGS := -O$(OPT) $(INCLUDE) $(LIBS)
endif

all: $(OBJ)
ifeq ($(BUILDTYPE),Debug)
	$(CC) -static $(OBJ) -o cRAYon$(EXT) $(CFLAGS)
else
	@echo Building cRAYon
	@$(CC) $(OBJ) -o cRAYon$(EXT) $(CFLAGS)
endif

%.o: %.c
ifeq ($(BUILDTYPE),Debug)
	$(CC) -static -c $< -o $@ $(INCLUDE) $(CFLAGS)
else
	@echo Building C object $<
	@$(CC) -c $< -o $@ $(INCLUDE)
endif

clean:
	rm -f $(OBJ)
	rm -f cRAYon*
