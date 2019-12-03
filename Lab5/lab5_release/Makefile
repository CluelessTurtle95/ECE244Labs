CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -g -std=c++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network -lsfml-audio
BUILD    := ./bin
OBJ_DIR  := ./obj
APP_DIR  := $(BUILD)
TARGET   := Lab5
INCLUDE  := -Iinclude/
SRC      :=                      \
    $(wildcard Lab5/*.cpp) \
    $(wildcard Lab5/*.hpp) \
    $(wildcard *.cpp) \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(APP_DIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*