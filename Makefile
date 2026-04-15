# ==============================
# Marinum Print Utility mPrint
# ==============================

CC = gcc
CFLAGS = -Wall -Wextra -O2 -Isrc

SRC_DIR = src
BIN_DIR = bin

OBJ_DIR = $(BIN_DIR)/obj

SRCS := $(shell find $(SRC_DIR) -name '*.c')

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/mprint

# Build

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $@"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(OBJS) -o $(TARGET)
	@echo "Build successfull! Run with ./$(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up build files..."
	@rm -rf $(BIN_DIR)

.PHONY: all clean
