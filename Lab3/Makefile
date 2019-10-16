CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -g -std=c++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network -lsfml-audio
BUILD    := ./exe
OBJ_DIR  := ./obj
APP_DIR  := $(BUILD)
TARGET   := Lab3
INCLUDE  := -Iinclude/
SRC      :=                      \
    $(wildcard src/module1/*.cpp) \
    $(wildcard src/module2/*.cpp) \
    $(wildcard src/module3/*.cpp) \
    $(wildcard parser/*.cpp)         \

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
