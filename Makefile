CC = g++

CFLAGS = -g -c -Wall -Wpedantic -Werror
LDFLAGS = 

SRC = $(wildcard src/*.cc)
HDR = $(wildcard src/*.h)
OBJ = $(SRC:src/%.cc=bin/obj/%.o)
BIN = bin/templater

CONFIG_DIR = ~/.config/templater/templates

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

bin/obj/%.o: src/%.cc $(HDR)
	$(CC) -o $@ $< $(CFLAGS)

clean: 
	rm -rf bin/*
	mkdir bin/obj

install: $(CONFIG_DIR)
	sudo cp $(BIN) /usr/$(BIN)
	cp -rf templates/* $(CONFIG_DIR)/

$(CONFIG_DIR):
	mkdir $(CONFIG_DIR)