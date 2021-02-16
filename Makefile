SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
PREFIX  := /usr/local

EXEC := $(BIN_DIR)/revBytes

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			:= gcc
CFLAGS	:= -Wall -O
LDFLAGS	:=
LDLIBS	:=

.PHONY:  all clean install

all:     $(EXEC)

$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

install: $(EXEC)
	sudo mkdir -p $(DESTDIR)$(PREFIX)/bin
	sudo cp $< $(DESTDIR)$(PREFIX)/bin
