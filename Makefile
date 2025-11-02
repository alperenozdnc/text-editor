CC = gcc
CFLAGS = -Wall -Wextra -lm -I./include

SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = txtedt

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET) run clean

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

run: $(TARGET) $(ARGS)
	@./$(TARGET) $(ARGS)
	@$(MAKE) clean --no-print-directory

