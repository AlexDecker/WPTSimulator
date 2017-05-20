CC = g++
MAIN = examples/main.cc
INC_DIR = include/
AUX_DIR = aux/
IND_DIR = aux/inductance/
OUT_DIR = build
CFLAGS = -lm

all: main.o Coil.o
	mkdir -p $(OUT_DIR)
	$(CC) -o $(OUT_DIR)/test $(OUT_DIR)/$^ -I$(INC_DIR) -I$(AUX_DIR)

Coil.o: inductance.o Coil.cc
	$(CC) -c -o $(OUT_DIR)/$@ $^ -I$(IND_DIR) -I$(INC_DIR) -I$(AUX_DIR) $(CFLAGS)

cinv.o: $(AUX_DIR)/cinv.cc
	$(CC) -c -o $(OUT_DIR)/$@ $< -I$(INC_DIR) -I$(AUX_DIR) $(CFLAGS)
	
main.o: $(MAIN)
	$(CC) -c -o $(OUT_DIR)/$@ -I$(INC_DIR) -I$(AUX_DIR) $<

inductance.o: $(IND_DIR)*.cc
	$(CC) -c -o $(OUT_DIR)/$@ $< $(CFLAGS)

clean:
	rm $(OUT_DIR)/*