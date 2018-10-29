CC := g++
LD := g++

CXXFLAGS := -g
LDFLAGS := -g -fopenmp -lprofiler -lsfml-graphics -lsfml-window -lsfml-system -llua -lluavm

SRC_DIR := debug events input game gui rendering resources scripting
BUILD_DIR := $(addprefix build/,$(SRC_DIR))

# ALL SRCS AND OBJECTS FOR BUILDING GAME
SRC := $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.cpp))
INCLUDES := $(addprefix -I,$(SRC_DIR)) -I/usr/include/SFML -I/usr/include/luavm
OBJ := $(patsubst %.cpp,build/%.o,$(SRC))

#SPECIFIC MODULE OBJS
EVENTS_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard events/*.cpp))
INPUT_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard input/*.cpp))
SCRIPTING_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard scripting/*.cpp))
GUI_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard gui/*.cpp))
RESOURCES_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard resources/*.cpp))
GAME_OBJ := $(patsubst %.cpp,build/%.o,$(wildcard game/*.cpp))

vpath %.cpp $(SRC_DIR)

.PHONY: clean events input coyoteiso peek

coyoteiso: coyoteiso
events: $(EVENTS_OBJ) $(INPUT_OBJ) dummy_main_events
input: $(INPUT_OBJ) $(EVENTS_OBJ) dummy_main_input
scripting: $(SCRIPTING_OBJ) dummy_main_scripting
gui: $(GUI_OBJ) $(SCRIPTING_OBJ) $(RESOURCES_OBJ) $(INPUT_OBJ) dummy_main_gui
game: $(GUI_OBJ) $(EVENTS_OBJ) $(RESOURCES_OBJ) $(INPUT_OBJ) dummy_main_game

resources: $(RESOURCES_OBJ) dummy_main_resources

define make-goal
$1/%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $$< -o $$@
endef

coyoteiso: main.cpp $(OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_events: dummy_main_events.cpp $(EVENTS_OBJ) $(INPUT_OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_input: dummy_main_input.cpp $(INPUT_OBJ) $(EVENTS_OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_scripting: dummy_main_scripting.cpp $(SCRIPTING_OBJ) $(EVENTS_OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_gui: dummy_main_gui.cpp $(GUI_OBJ) $(EVENTS_OBJ) $(SCRIPTING_OBJ) $(RESOURCES_OBJ) $(INPUT_OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_game: dummy_main_game.cpp $(GUI_OBJ) $(EVENTS_OBJ) $(RESOURCES_OBJ) $(INPUT_OBJ)

	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

dummy_main_resources: dummy_main_resources.cpp $(RESOURCES_OBJ)
	$(LD) $(INCLUDES) $^ -o $@ $(LDFLAGS)

# build/events/%.o: %.cpp
# 	$(CC) $(CXXFLAGS) $(INCLUDES) -c $$< -o $$@

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir))))

clean:
	rm $(OBJ)
