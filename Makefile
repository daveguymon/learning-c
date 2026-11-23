CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
TARGET := build/basic_calculator
CALCULATOR_OBJECT := build/calculator.o
APP_OBJECT := build/basic_calculator.o
TEST_TARGET := build/test_calculator
TEST_OBJECT := build/test_calculator.o

.PHONY: build run test clean

build: $(TARGET)

$(TARGET): $(APP_OBJECT) $(CALCULATOR_OBJECT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJECT) $(CALCULATOR_OBJECT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@

build/basic_calculator.o: basic_calculator.c calculator.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/calculator.o: calculator.c calculator.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/test_calculator.o: tests/test_calculator.c calculator.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I. -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) $(APP_OBJECT) $(CALCULATOR_OBJECT) $(TEST_OBJECT)
