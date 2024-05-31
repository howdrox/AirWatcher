# Define directories
SRC_DIR := src
TEST_DIR := tests
TARGET_DIR := target

# Define compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -I$(SRC_DIR) # Include the src directory for header files
LDFLAGS := -lcppunit

# # Define target executable
# APP_TARGET := $(TARGET_DIR)/airwalker
# TEST_TARGET := $(TARGET_DIR)/test_airwalker

# # Define source and object files
# SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

# OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC_FILES))
# TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(TEST_FILES))

# # Default target
# all: $(APP_TARGET) $(TEST_TARGET)

# # Rule to build the application executable
# $(APP_TARGET): $(OBJ_FILES)
# 	$(CXX) $(CXXFLAGS) -o $@ $^

# # Rule to build the test executable
# $(TEST_TARGET): $(TEST_OBJ_FILES)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# # Rule to build object files
# $(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TARGET_DIR)
# 	$(CXX) $(CXXFLAGS) -std=c++11 -fpermissive -o $@ $<

# $(TARGET_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TARGET_DIR)
# 	$(CXX) $(CXXFLAGS) -std=c++11 -fpermissive -o $@ $<

# # Create the build directory if it does not exist
# $(TARGET_DIR):
# 	mkdir -p $(TARGET_DIR)

# # Clean up build artifacts
# clean:
# 	rm -rf $(TARGET_DIR)

# .PHONY: all clean

CXX = g++
CXXFLAGS = -Wall #-Wextra -std=c++11
TARGET = my_program
OBJECTS = src/Time.o src/Cleaner.o src/User.o \
		src/PrivateUser.o src/Provider.o src/GovernmentAgent.o src/Measurement.o \
		src/Sensor.o src/System.o src/Service.o src/main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

Time.o: 
	$(CXX) $(CXXFLAGS) -c Time.cpp

Cleaner.o: 
	$(CXX) $(CXXFLAGS) -c Cleaner.cpp

User.o: 
	$(CXX) $(CXXFLAGS) -c User.cpp

PrivateUser.o: 
	$(CXX) $(CXXFLAGS) -c PrivateUser.cpp

Provider.o: 
	$(CXX) $(CXXFLAGS) -c Provider.cpp

GovernmentAgent.o: 
	$(CXX) $(CXXFLAGS) -c GovernmentAgent.cpp

Measurement.o: 
	$(CXX) $(CXXFLAGS) -c Measurement.cpp

Sensor.o: 
	$(CXX) $(CXXFLAGS) -c Sensor.cpp

System.o: 
	$(CXX) $(CXXFLAGS) -c System.cpp

Service.o: 
	$(CXX) $(CXXFLAGS) -c Service.cpp

main.o: 
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJECTS)
