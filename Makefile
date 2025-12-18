# =========================
# Compiler and files
# =========================
CC = gcc

# List all your .c files here
IN = main.c \
     src/main_state.c \
     src/game_constants.c \
     src/player.c \
     src/fish.c \
     src/glad/glad.c

OUT = main

# Default flags
CFLAGS = -Wall -DGLFW_INCLUDE_NONE
IFLAGS = -I. -I./include -I./src

# =========================
# OS detection
# =========================
ifeq ($(OS),Windows_NT)
    RM = if exist $(OUT).exe del /Q $(OUT).exe
    RUN = $(OUT).exe
    LFLAGS = libs/glfw/libglfw3.a -lopengl32 -lgdi32 -luser32 -lkernel32 -lm
    IFLAGS += -I./libs/glfw/include
else
    RM = rm -f
    RUN = ./$(OUT)
    LFLAGS = libs/glfw/libglfw3.a -ldl -lm
    IFLAGS += -I./libs/glfw/include
endif

# =========================
# Build rules
# =========================
.SILENT: all

all: clean build run

# Clean
clean:
	$(RM)

# Build
build: $(IN) include/main_state.h include/stb_image.h
	$(CC) $(IN) -o $(OUT) $(CFLAGS) $(LFLAGS) $(IFLAGS)

# Run
run: $(OUT)
	$(RUN)
