CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
TARGET := build/basic_calculator

.PHONY: build run

build: $(TARGET)

$(TARGET): basic_calculator.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET)
	./$(TARGET)
