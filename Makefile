NAME    := revBytes

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
PREFIX  := /usr/local

EXEC := $(BIN_DIR)/$(NAME)

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC		:= gcc
CFLAGS	:= -Wall -O -Werror -Wextra
LDFLAGS	:=
LDLIBS	:=

.PHONY:  all clean install fclean

all: $(EXEC)

$(EXEC): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

fclean:
	@$(RM) -rv $(EXEC)

install: $(EXEC)
	sudo mkdir -p $(DESTDIR)$(PREFIX)/bin
	sudo cp $< $(DESTDIR)$(PREFIX)/bin
