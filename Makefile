# Global Files
TARGET = main
MAINSRCS = main.cpp
STATICSRCS = delta_time.cpp ttf.cpp renderer.cpp
UTILITYSRCS = sdl_compare_surfaces.cpp
UISRCS = ui_init.cpp main_menu.cpp
WORLDSRCS = world.cpp map.cpp tile.cpp entity.cpp player.cpp
AUDIOSRCS = music.cpp
# TBC Files
COMPONENTSRCS = battle_character.cpp battle_move.cpp battle_status.cpp priority_list.cpp battle_ui.cpp
CHARACTERSRCS = zerachiel.cpp livya.cpp cicero.cpp
STATUSSRCS = duel_with_zerachiel.cpp heal_blocked.cpp contract_with_livya.cpp cicero_allin.cpp
TBCSRCS = battle_system.cpp battle_render.cpp
	TBCSRCS += $(patsubst %.cpp, components/%.cpp, $(COMPONENTSRCS))
	TBCSRCS += $(patsubst %.cpp, characters/%.cpp, $(CHARACTERSRCS))
	TBCSRCS += $(patsubst %.cpp, status/%.cpp, $(STATUSSRCS))
# All Sources
SRCS = $(patsubst %.cpp, game/src/%.cpp, $(MAINSRCS))
	SRCS += $(patsubst %.cpp, game/src/static/%.cpp, $(STATICSRCS))
	SRCS += $(patsubst %.cpp, game/src/utility/%.cpp, $(UTILITYSRCS))
	SRCS += $(patsubst %.cpp, game/src/ui/%.cpp, $(UISRCS))
	SRCS += $(patsubst %.cpp, game/src/tbc/%.cpp, $(TBCSRCS))
	SRCS += $(patsubst %.cpp, game/src/world/%.cpp, $(WORLDSRCS))
	SRCS += $(patsubst %.cpp, game/src/audio/%.cpp, $(AUDIOSRCS))
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

#compiler
CC = g++
CFLAGS = -Wall -std=c++23 -O3 -pedantic -Wextra

#linker
CFLAGS += -fsanitize=address -fno-omit-frame-pointer -g3
LDFLAGS += -fsanitize=address

#libraries
CFLAGS += $(shell pkg-config --cflags sdl2)
LDFLAGS += $(shell pkg-config --libs sdl2)
CFLAGS += $(shell pkg-config --cflags SDL2_image)
LDFLAGS += $(shell pkg-config --libs SDL2_image)
CFLAGS += $(shell pkg-config --cflags SDL2_mixer)
LDFLAGS += $(shell pkg-config --libs SDL2_mixer)
CFLAGS += $(shell pkg-config --cflags SDL2_ttf)
LDFLAGS += $(shell pkg-config --libs SDL2_ttf)
CFLAGS += $(shell pkg-config --cflags SDL2_gfx)
LDFLAGS += $(shell pkg-config --libs SDL2_gfx)

#compilation
all: $(TARGET)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@ 

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)