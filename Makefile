# Compiler and files
CC = gcc
IN = main.c src/main_state.c src/glad/glad.c
OUT = main

# Default flags
CFLAGS = -Wall -DGLFW_INCLUDE_NONE
IFLAGS = -I. -I./include

# OS detection
ifeq ($(OS),Windows_NT)
    RM = if exist $(OUT) del /Q $(OUT)
    OUT := $(OUT).exe
    LFLAGS = libs/glfw/libglfw3.a -lopengl32 -lgdi32 -luser32 -lkernel32 -lm
    IFLAGS += -I./libs/glfw/include
    RUN = $(OUT)
else
    RM = rm -f
    LFLAGS = libs/glfw/libglfw3.a -ldl -lm
    IFLAGS += -I./libs/glfw/include
    RUN = ./$(OUT)
endif

.SILENT: all
all: clean build run

# Clean
clean:
	$(RM) $(OUT)

# Build
build: $(IN) include/main_state.h include/stb_image.h
	$(CC) $(IN) -o $(OUT) $(CFLAGS) $(LFLAGS) $(IFLAGS)

# Run
run: $(OUT)
	$(RUN)
