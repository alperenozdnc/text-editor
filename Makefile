SRC_DIR = ./src
.PHONY: all clean

all: main.o 
	@./run
	@$(MAKE) --no-print-directory clean

main.o:
	@gcc $(SRC_DIR)/main.c -o run

clean:
	@rm ./run
