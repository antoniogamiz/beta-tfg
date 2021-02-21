SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
PROGRESS_DIR = progress
PPM_FILE := result

EXE := $(BIN_DIR)/color.exe
SRC := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_DIRS := $(dir $(OBJ))
CPPFLAGS := -Iinclude
CXXFLAGS   := -g -std=c++2a -Wall
LDFLAGS  := -Llib
LDLIBS   := -lpthread
CXX := g++

.PHONY: all clean start

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) setup
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

setup:
	mkdir -p $(OBJ_DIRS)

start:
	rm -rf $(PROGRESS_DIR)
	chmod a+x $(EXE)
	mkdir -p $(PROGRESS_DIR)
	$(EXE) > $(PPM_FILE).ppm
	pnmtopng $(PPM_FILE).ppm > $(PPM_FILE).png
	rm -rf $(PROGRESS_DIR)
	code $(PPM_FILE).png

clean:
	@echo $(SRC)
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
