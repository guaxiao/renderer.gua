.PHONY : mingw osx linux clean

CC = g++
CFLAGS = -Wall -Isrc
LDFLAGS :=


GUA3D := \
src/window.cpp \
src/canvas.cpp \
src/color.cpp \
src/vector.cpp


SRC := $(GUA3D)


# all: osx


mingw : OS := WINDOWS
mingw : TARGET := gua3d.exe
mingw : CFLAGS += -std=c++11 -ISDL-1.2.15/include -LSDL-1.2.15/lib 
mingw : LDFLAGS += -lmingw32 -mwindows -lSDLmain -lSDL
mingw : SRC += platform/win/main.cpp

mingw : $(SRC) gua


osx : OS := OSX
osx : TARGET := gua3d
osx : FRAMEWORKS := -framework Cocoa -framework SDL
# osx : CFLAGS += 
osx : LDFLAGS += $(FRAMEWORKS)
osx : SRC += platform/osx/main.mm platform/osx/SDLMain.m

osx : $(SRC) gua


linux : OS := linux
linux : TARGET := gua3d
linux : CFLAGS += -std=c++11 
linux : LDFLAGS += -lSDL
linux : SRC += platform/linux/main.cpp

linux : $(SRC) gua


gua :
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean :
	-mv gua3d /tmp
