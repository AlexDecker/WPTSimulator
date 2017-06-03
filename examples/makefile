#add your file.o here to compile it on standalone mode. Add its function in main's switch also.
OBJECTS = example1.o example2.o example3.o example4.o example5.o
CC = g++
INC_DIR = -I"../include" -I"../aux/matrix" -I"../aux/inductance"
OUT_DIR = ../build
CFLAGS = -lm
%.o: %.cc
	mkdir -p $(OUT_DIR)
	$(CC) -c -o $(OUT_DIR)/$@ $< $(INC_DIR) $(CFLAGS)

all: $(OBJECTS) main.o
