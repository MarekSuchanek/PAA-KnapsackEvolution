#=== DIRS
BIN=./bin
SRC=./src
BUILD=./build

#=== COMPILER & LINKER
LD=g++
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11 -g

#=== FINAL APP
TARGET=$(BIN)/knapevo
#=== ALL OBJS
OBJS=$(BUILD)/main.o $(BUILD)/evolution.o $(BUILD)/individual.o $(BUILD)/knapsack.o $(BUILD)/random.o $(BUILD)/crossover.o $(BUILD)/mutation.o

#=== BASIC COMMANDS
.PHONY: all
all: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET) ${ARGS}

.PHONY: clean
clean:
	rm -rf $(BIN) $(BUILD)

#=== LINK TOGETHER
$(TARGET): $(OBJS)
	mkdir -p $(BIN)
	$(LD) -o $@ $(OBJS)

#=== BUILD ALL OBJS
$(BUILD)/%o: $(SRC)/%cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

#=== DEPENDENCISIES (one.o -> one.cpp + multiple.hpp)
$(BUILD)/crossover.o: $(SRC)/crossover.cpp $(SRC)/crossover.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/evolution.o: $(SRC)/evolution.cpp $(SRC)/evolution.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp $(SRC)/crossover.hpp $(SRC)/mutation.hpp
$(BUILD)/individual.o: $(SRC)/individual.cpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/knapsack.o: $(SRC)/knapsack.cpp $(SRC)/knapsack.hpp
$(BUILD)/mutation.o: $(SRC)/mutation.cpp $(SRC)/mutation.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/random.o: $(SRC)/random.cpp $(SRC)/random.hpp
$(BUILD)/main.o: $(SRC)/main.cpp $(SRC)/evolution.hpp $(SRC)/knapsack.hpp $(SRC)/crossover.hpp $(SRC)/mutation.hpp
