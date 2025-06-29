TARG = falcon

SRC_DIR = src
INC_DIR = inc
#LIB_DIR = lib

CC = gcc
CFLAGS = -Wall -Wextra -g -I$(SRC_DIR) -I$(INC_DIR)
LDFLAGS = -lcrypto -lsqlite3

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

all: $(TARG)

$(TARG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARG)
