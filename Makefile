# Define directories
SRC_DIR := src
TEST_DIR := tests
TARGET_DIR := target

# Define compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -I$(SRC_DIR) # Include the src directory for header files
LDFLAGS := -lcppunit

# Define target executable
APP_TARGET := $(TARGET_DIR)/airwalker
TEST_TARGET := $(TARGET_DIR)/test_airwalker

# Define source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)

OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(SRC_FILES))
TEST_OBJ_FILES := $(patsubst $(TEST_DIR)/%.cpp, $(TARGET_DIR)/%.o, $(TEST_FILES))

# Default target
all: $(APP_TARGET) $(TEST_TARGET)

# Rule to build the application executable
$(APP_TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
$(TARGET_DIR)/%.o: $(SRC_DIR)/%.cpp | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -std=c++11 -fpermissive -o $@ $<

$(TARGET_DIR)/%.o: $(TEST_DIR)/%.cpp | $(TARGET_DIR)
	$(CXX) $(CXXFLAGS) -std=c++11 -fpermissive -o $@ $<

# Create the build directory if it does not exist
$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Clean up build artifacts
clean:
	rm -rf $(TARGET_DIR)

.PHONY: all clean
