#must be a direct son of root
OUT_DIR = build

CC = g++
AR = ar

INC_DIR = -I"../include/" -I"../aux/matrix/" -I"../aux/inductance/"

BIN = standalone

LIB = libwptsim.a

#folder where your NS3 code is
NS3_DIR = ../NS3_DIR

#make a standalone simulator
all: objects
	$(CC) -o $(OUT_DIR)/$(BIN) $(OUT_DIR)/*.o $(INC_DIR)
	@echo "BUILD SUCCESSFUL"
	
ns3: objects
	mkdir -p $(NS3_DIR)
	$(AR) -cvq $(NS3_DIR)/$(LIB) $(OUT_DIR)/*.o
	@echo "BUILD SUCCESSFUL"

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
	rm -f $(NS3_DIR)/$(LIB)