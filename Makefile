SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
PROGRESS_DIR = progress
PPM_FILE := result

EXE := $(BIN_DIR)/color
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude
CXXFLAGS   := -g -std=c++2a -Wall
LDFLAGS  := -Llib
LDLIBS   := -lpthread
CXX := g++

.PHONY: all clean

all: $(EXE) progress

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

progress:
	rm -rf $(PROGRESS_DIR)
	chmod a+x $(EXE)
	mkdir -p $(PROGRESS_DIR)
	$(EXE) > $(PPM_FILE).ppm
	pnmtopng $(PPM_FILE).ppm > $(PPM_FILE).png
	rm -rf $(PROGRESS_DIR)
	code $(PPM_FILE).png

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)
