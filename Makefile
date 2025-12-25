# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -std=c11

# Executable name
TARGET = main

SRC = main.c

ifeq ($(OS),Windows_NT)
	EXE = .exe
	RM = del /Q
	RUN = $(TARGET)$(EXE)
else
	EXE =
	RM = rm -f
	RUN = ./$(TARGET)
endif

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)$(EXE)

# Compile + run
run: $(TARGET)
	$(RUN)

clean:
	$(RM) $(TARGET)$(EXE)
