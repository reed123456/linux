.PHONY: main clean
TARGET=mian

SRCS=$(wildcard *.c)
BASE_DIR=$(shell pwd)
OBJ_DIR=$(BASE_DIR)/obj
$(shell mkdir -p $(OBJ_DIR))
OBJS:=$(SRCS:.c=.o)
OBJS:=$(addprefix $(OBJ_DIR)/, $(OBJS))

CC=gcc

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o : %.c
	$(CC) -c -g $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

#rebuild : clean all
