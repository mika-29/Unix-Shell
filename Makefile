#Compiler and Compiler flags 
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 

# Name of the output executable
TARGET = mysh 

# Builds the shell 
all: $(TARGET)

# Build rule for the shell executable 
$(TARGET): main.c parser.c
	$(CC) $(CFLAGS) main.c parser.c -o $(TARGET) 

# Removes generated files  
clean:
	rm -f $(TARGET)