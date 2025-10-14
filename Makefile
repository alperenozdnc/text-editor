SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = run

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/file_exists.o

all: run_and_clean

run_and_clean: $(TARGET)
	@./$(TARGET) $(ARGS)
	@$(MAKE) clean --no-print-directory

$(TARGET): $(OBJS)
	@$(CC) $(OBJS) -o $(TARGET)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/file_exists.o: $(SRC_DIR)/utils/file_exists.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

