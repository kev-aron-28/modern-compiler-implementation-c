CC = gcc

# Compiler flags
CFLAGS = -Iinclude

# Source and object files
SRCDIR = src
INCDIR = include
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXEC = my_program

# Default target
all: $(EXEC)

# Link objects to create executable
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

# Compile source files to object files
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJECTS) $(EXEC)
