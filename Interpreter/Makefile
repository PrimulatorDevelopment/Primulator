# Compiler and flags
CC = gcc
CFLAGS = -Wall -I$(INCLUDE_DIR)

# Directories
INCLUDE_DIR = ./Include
SRC_DIR = ./Source
BUILD_DIR = ./build
BIN_DIR = ./bin

# Source files and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) Interpreter.c
OBJ_FILES = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRC_FILES)))

# Output executable
EXEC = $(BIN_DIR)/program_name

# Targets
all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_FILES) -o $@

# Rule to compile .c files into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/Interpreter.o: Interpreter.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create build directory if it doesn't exist
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean