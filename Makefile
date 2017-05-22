CC = g++
MAIN = examples/main.cc
INC_DIR = -I"include/" -I"aux/" -I"aux/inductance/"
OUT_DIR = build
CFLAGS = -lm

%.o: %.c
	$(CC) -c -o $(OUT_DIR)/$@ $< $(INC_DIR) $(CFLAGS)

all: main.o inductance.o
	mkdir -p $(OUT_DIR)
	$(CC) -o $(OUT_DIR)/test $(OUT_DIR)/$^ $(INC_DIR) $(CFLAGS)

clean:
	rm $(OUT_DIR)/*