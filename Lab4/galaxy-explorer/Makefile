CXX      := g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -g -std=c++11
LDFLAGS  := -L/usr/lib -lstdc++ -lm -lsfml-graphics -lsfml-system -lsfml-window -lsfml-network -lsfml-audio -lXrandr -lpthread -lrt -lGL -lSM -lICE -lX11 -lXext -lfreetype -ljpeg -l:libFLAC.so.8 -lvorbis -lvorbisenc -logg -lvorbisfile
BUILD    := ./bin
OBJ_DIR  := ./obj
APP_DIR  := $(BUILD)
TARGET   := galaxy-explorer
INCLUDE  := -Iinclude/
SRC      :=                      \
    $(wildcard src/galaxy-explorer/*.cpp) \
    $(wildcard src/galaxy-explorer/*.hpp) \
    $(wildcard src/*.cpp) \

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
	cp assignment_objects/debug/galaxy-explorer/*.o $(OBJ_DIR)/