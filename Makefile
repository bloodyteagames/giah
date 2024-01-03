SRC = src/*.cpp
CFLAGS = -std=c++20 -Wall -Wextra -pedantic -ggdb -O0
INC = -Iinclude/
NAME = giah
OUT = $(NAME)

RAYLIB = lib/raylib/src

LIB = -L$(RAYLIB)

ifeq ($(OS), Windows_NT)
	LINK = -lraylib -lopengl32 -lgdi32 -lwinmm
	OUT = bin/windows/$(NAME).exe
	REM = del bin\windows\$(NAME).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		LINK = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
		OUT = bin/linux/$(NAME)
		REM = rm -rf $(OUT)
	endif
endif

all: $(SRC)
	$(REM)
	g++ $(SRC) -o $(OUT) $(INC) $(LINK) $(CFLAGS)
	./$(OUT)
