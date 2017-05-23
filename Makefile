OUT_DIR = build
CC = g++
INC_DIR = -I"../include/" -I"../aux/matrix/" -I"../aux/inductance/"

all:
	make -C aux/matrix/
	make -C aux/inductance/
	make -C src/
	make -C examples/
	$(CC) -o $(OUT_DIR)/example $(OUT_DIR)/*.o $(INC_DIR)

run:
	cd build && ./example && cd ../
	
clean:
	rm -f $(OUT_DIR)/*.o