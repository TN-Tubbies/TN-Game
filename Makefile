# Files
TARGET = main
MAINSRCS = main.c
UISRCS = ui_init.c
TBCSRCS =
SRCS = $(patsubst %.c, game/src/%.c, $(MAINSRCS))
	SRCS += $(patsubst %.c, game/src/ui/%.c, $(UISRCS))
	SRCS += $(patsubst %.c, game/src/tbc/%.c, $(TBCSRCS))
OBJS = $(patsubst %.c, %.o, $(SRCS))

#compiler
CC = g++
CFLAGS = -Wall -std=c++23 -pedantic -O3

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
# CFLAGS += $(shell pkg-config --cflags sdl2_gfx)
# LDFLAGS += $(shell pkg-config --libs sdl2_gfx)

#compilation
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@ 

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)