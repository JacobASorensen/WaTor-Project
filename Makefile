
# Directories
TARGET = JS_WaTor
INCLUDE_DIR := include
OBJ_DIR := obj
SRC_DIR := src

# Files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))
TARGET := JS_Wator

#compiler flags
CXX := g++
CXXFLAGS =  -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -std=c++17 -I${INCLUDE_DIR}
# -Werror

# compile it!
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# dependencies.... much better than manually entering it all!
$(TARGET): $(OBJ)

.PHONY: all clean

all: ${TARGET}

clean:
	rm -rf ${OBJ_DIR} ${TARGET}
	rm -rd ${OBJDIR}
clear:
	make clean
	clear
	clear
	make
