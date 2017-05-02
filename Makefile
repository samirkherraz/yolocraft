SRC_DIR = ./src/
BIN_DIR = ./bin/
OBJ_DIR = ./obj/

OBJ_FLAGS = -c 
CPP_PLAGS = -Wall -std=c++11 -g
RELEASE_FLAGS = -std=c++11 -O1 -O3 -O2
SDL_LIBS = -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -lSDL2_mixer
Box2D_LIBS = -lBox2D

SRC_FILES = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
FILES = $(notdir $(SRC_FILES:.cpp=))
H_FILES = $(addprefix $(SRC_DIR),$(notdir $(SRC_FILES:.cpp=.h)))
OBJ_FILES = $(addprefix $(OBJ_DIR),$(notdir $(SRC_FILES:.cpp=.o)))

OUTPUT = yolocraft

release: $(SRC_DIR)main.cpp $(FILES)
	g++ $(RELEASE_FLAGS) $(OBJ_FILES) $(SRC_DIR)main.cpp -o $(BIN_DIR)$(OUTPUT) $(Box2D_LIBS) $(SDL_LIBS)


all: $(SRC_DIR)main.cpp $(FILES)
	g++ $(CPP_PLAGS) $(OBJ_FILES) $(SRC_DIR)main.cpp -o $(BIN_DIR)$(OUTPUT) $(Box2D_LIBS) $(SDL_LIBS)

$(FILES): $(H_FILES)
	g++ $(CPP_PLAGS) $(OBJ_FLAGS) $(SRC_DIR)$@.cpp -o $(OBJ_DIR)$@.o
	
	 
clean: 
		rm -vf $(OBJ_FILES)
		rm -vf $(BIN_DIR)$(OUTPUT)
