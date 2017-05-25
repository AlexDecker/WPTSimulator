CC = g++
INC_DIR = -I"../include" -I"../aux/matrix" -I"../aux/inductance"
OUT_DIR = ../build
CFLAGS = -lm
%.o: %.cc
	mkdir -p $(OUT_DIR)
	$(CC) -c -o $(OUT_DIR)/$@ $< $(INC_DIR) $(CFLAGS)

all: main.o
