# Define directories
SRC_DIR := src
TEST_DIR := tests
TARGET_DIR := target

# Define compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS := -lcppunit

# Define target executable
APP_TARGET := $(TARGET_DIR)/airwalker
TEST_TARGET := $(TARGET_DIR)/test_airwalker

# Define source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_MAIN := $(patsubst $(TEST_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(TEST_FILES))
TEST_OBJ_FILES := $(filter-out $(TARGET_DIR)/main.o, $(OBJ_FILES))

# Default target
all: $(APP_TARGET) $(TEST_TARGET)

# Rule to build the application executable
$(APP_TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJ_MAIN) $(TEST_OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

# Rule to build object files
$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(TARGET_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Create the build directory if it does not exist
$(TARGET_DIR):
	mkdir $(TARGET_DIR)

# Clean up build artifacts
clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean

# CXX = g++
# CXXFLAGS = -Wall #-Wextra -std=c++11
# TARGET = my_program
# OBJECTS = $(TARGET_DIR)/Time.o $(TARGET_DIR)/Cleaner.o $(TARGET_DIR)/User.o \
# 		$(TARGET_DIR)/PrivateUser.o $(TARGET_DIR)/Provider.o $(TARGET_DIR)/GovernmentAgent.o $(TARGET_DIR)/Measurement.o \
# 		$(TARGET_DIR)/Sensor.o $(TARGET_DIR)/System.o $(TARGET_DIR)/Service.o $(TARGET_DIR)/main.o



# all: $(TARGET)

# $(TARGET): $(OBJECTS)
# 	$(CXX) $(OBJECTS) -o $(TARGET)

# # Create the build directory if it does not exist
# $(TARGET_DIR):
# 	mkdir $(TARGET_DIR)

# $(TARGET_DIR)/Time.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Time.cpp -o $(TARGET_DIR)/Time.o

# $(TARGET_DIR)/Cleaner.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Cleaner.cpp -o $(TARGET_DIR)/Cleaner.o

# $(TARGET_DIR)/User.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/User.cpp -o $(TARGET_DIR)/User.o

# $(TARGET_DIR)/PrivateUser.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/PrivateUser.cpp -o $(TARGET_DIR)/PrivateUser.o

# $(TARGET_DIR)/Provider.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Provider.cpp -o $(TARGET_DIR)/Provider.o

# $(TARGET_DIR)/GovernmentAgent.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/GovernmentAgent.cpp -o $(TARGET_DIR)/GovernmentAgent.o

# $(TARGET_DIR)/Measurement.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Measurement.cpp -o $(TARGET_DIR)/Measurement.o

# $(TARGET_DIR)/Sensor.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Sensor.cpp -o $(TARGET_DIR)/Sensor.o

# $(TARGET_DIR)/System.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/System.cpp -o $(TARGET_DIR)/System.o

# $(TARGET_DIR)/Service.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Service.cpp -o $(TARGET_DIR)/Service.o

# $(TARGET_DIR)/main.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(TARGET_DIR)/main.o

# clean:
# 	rm -f $(TARGET) $(OBJECTS)
