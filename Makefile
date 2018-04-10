BIN=./bin
SRC=./src
BUILD=./build

LD=g++
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11 -g
TARGET=$(BIN)/knapevo

all: $(TARGET)

run: $(TARGET)
	./$(TARGET) ${ARGS}

$(TARGET): $(BUILD)/main.o $(BUILD)/evolution.o $(BUILD)/individual.o $(BUILD)/knapsack.o $(BUILD)/random.o $(BUILD)/crossover.o $(BUILD)/mutation.o
	mkdir -p $(BIN)
	$(LD) -o $@ $(BUILD)/main.o $(BUILD)/evolution.o $(BUILD)/individual.o $(BUILD)/knapsack.o $(BUILD)/random.o $(BUILD)/crossover.o $(BUILD)/mutation.o

$(BUILD)/%o: $(SRC)/%cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN) $(BUILD)

$(BUILD)/crossover.o: $(SRC)/crossover.cpp $(SRC)/crossover.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/evolution.o: $(SRC)/evolution.cpp $(SRC)/evolution.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp $(SRC)/crossover.hpp $(SRC)/mutation.hpp
$(BUILD)/individual.o: $(SRC)/individual.cpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/knapsack.o: $(SRC)/knapsack.cpp $(SRC)/knapsack.hpp
$(BUILD)/mutation.o: $(SRC)/mutation.cpp $(SRC)/mutation.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/random.o: $(SRC)/random.cpp $(SRC)/random.hpp
$(BUILD)/main.o: $(SRC)/main.cpp $(SRC)/evolution.hpp $(SRC)/knapsack.hpp $(SRC)/crossover.hpp $(SRC)/mutation.hpp
