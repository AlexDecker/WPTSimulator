CC = g++
CFLAGS = -lm
OUT_DIR = ../../build

all: rdivide.o diff.o inductance_neuman_initialize.o linspace.o sqrt.o rtGetInf.o inductance_neuman.o sum.o inductance_neuman_emxAPI.o inductance_neuman_terminate.o rtGetNaN.o inductance_neuman_emxutil.o power.o rt_nonfinite.o interp1.o

%.o: %.cc %.h
	mkdir -p $(OUT_DIR)
	$(CC) -c -o $(OUT_DIR)/$@ $< $(CFLAGS)
