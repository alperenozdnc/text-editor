CC = gcc
CFLAGS = -Wall -Wextra -lm -I./include

SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = txtedt

TEST_DIR = ./test
TEST_TARGET = run_tests

# All editor sources
SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Editor objects **excluding main.c** for testing
EDITOR_OBJS := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

# Test sources
TEST_SRCS := $(shell find $(TEST_DIR) -name '*.c')
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/test_%.o)

# === Rules ===

all: $(TARGET) run clean

# Build editor executable
$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

# Build object files from src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Run editor
run: $(TARGET) $(ARGS)
	@./$(TARGET) $(ARGS)
	@$(MAKE) clean --no-print-directory

# === Testing ===

# Build object files from test
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build test executable
$(TEST_TARGET): $(EDITOR_OBJS) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(EDITOR_OBJS) $(TEST_OBJS) -o $@

# Run tests
tests: $(TEST_TARGET)
	@./$(TEST_TARGET)
	@rm ./$(TEST_TARGET)

# Clean all objects and executables
clean:
	@rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

