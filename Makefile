SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = run

CC = gcc
CFLAGS = -lm -Wall -Wextra

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: run_and_clean

run_and_clean: $(TARGET)
	@./$(TARGET) $(ARGS)
	@$(MAKE) clean --no-print-directory

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

