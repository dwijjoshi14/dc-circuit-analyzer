CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
SRC      = src/main.cpp src/circuit.cpp
TARGET   = circuit_analyzer

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

demo: $(TARGET)
	./$(TARGET) --demo

clean:
	rm -f $(TARGET)

.PHONY: all demo clean
