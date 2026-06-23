# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -g

# Project files
TARGET = todomanager
SRCS = main.c tasks.c
OBJS = $(SRCS:.c=.o)
HEADERS = tasks.h

# Default target when you just type 'make'
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files (object files and executable)
clean:
	rm -f $(OBJS) $(TARGET)

# Build and run the program in one command
run: $(TARGET)
	./$(TARGET)

# Check for memory leaks using Valgrind
valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Phony targets to prevent conflicts with file names
.PHONY: all clean run valgrind
