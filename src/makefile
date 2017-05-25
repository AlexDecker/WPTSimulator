CC = g++
OUT_DIR = ../build
INC_DIR = -I"../include/" -I"../aux/matrix/" -I"../aux/inductance/"
CFLAGS = -lm

%.o: %.cc
	mkdir -p $(OUT_DIR)
	$(CC) -c -o $(OUT_DIR)/$@ $^ $(INC_DIR) $(CFLAGS)

all:Coil.o GlobalCoupler.o Resonator.o util.o
