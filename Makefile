BIN=./bin
SRC=./src
BUILD=./build

LD=g++
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++11
TARGET=$(BIN)/knapsack

all: $(TARGET)

$(TARGET): $(BUILD)/main.o $(BUILD)/evolution.o $(BUILD)/individual.o $(BUILD)/knapsack.o $(BUILD)/random.o
	mkdir -p $(BIN)
	$(LD) -o $@ $(BUILD)/main.o $(BUILD)/evolution.o $(BUILD)/individual.o $(BUILD)/knapsack.o $(BUILD)/random.o

$(BUILD)/%o: $(SRC)/%cpp
	mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN) $(BUILD)

$(BUILD)/evolution.o: $(SRC)/evolution.cpp $(SRC)/evolution.hpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/individual.o: $(SRC)/individual.cpp $(SRC)/individual.hpp $(SRC)/knapsack.hpp
$(BUILD)/knapsack.o: $(SRC)/knapsack.cpp $(SRC)/knapsack.hpp
$(BUILD)/random.o: $(SRC)/random.cpp $(SRC)/random.hpp
$(BUILD)/main.o: $(SRC)/main.cpp $(SRC)/evolution.hpp $(SRC)/knapsack.hpp
