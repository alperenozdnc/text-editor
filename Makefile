SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = run

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/file_exists.o $(OBJ_DIR)/is_valid_args.o $(OBJ_DIR)/printl.o

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

$(OBJ_DIR)/is_valid_args.o: $(SRC_DIR)/utils/is_valid_args.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/printl.o: $(SRC_DIR)/utils/printl.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -rf $(OBJ_DIR) $(TARGET)

