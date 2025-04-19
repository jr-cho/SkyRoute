# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Source files
SRC = MAIN/main.cpp GRAPH/graph.cpp
OBJ = $(SRC:.cpp=.o)

# Output binary
TARGET = sky_route.out

# Default target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Clean build files
clean:
	rm -f $(TARGET) $(OBJ)

# Run the program
run: all
	./$(TARGET)

