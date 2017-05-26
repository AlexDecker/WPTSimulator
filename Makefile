#must be a direct son of root
OUT_DIR = build
CC = g++
INC_DIR = -I"../include/" -I"../aux/matrix/" -I"../aux/inductance/"
BIN = standalone

#make a standalone simulator
all: objects
	$(CC) -o $(OUT_DIR)/$(BIN) $(OUT_DIR)/*.o $(INC_DIR)

objects:
	make -C aux/matrix/
	make -C aux/inductance/
	make -C src/
	make -C examples/
	
run:
	cd $(OUT_DIR) && ./$(BIN) $(EXAMPLE) && cd ../
	
clean:
	rm -f $(OUT_DIR)/*.o
	rm -f $(OUT_DIR)/$(BIN)