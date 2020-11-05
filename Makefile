# compiler
CC = g++

# compiler flags
CXXFLAGS = -Wall -gstabs -std=c++11 $(INC) -static-libgcc -static-libstdc++ \
		   -Wno-narrowing -Wno-sign-compare -Wno-reorder

# executable name
BIN = chat

# object files
ENGINE_OBJ = Application.o Graphics.o Scene.o Object.o AssetManager.o \
			 Vector2.o Transform.o Input.o TextObject.o
APP_OBJ = Main.o Chat.o DefaultScene.o ChatWindow.o EditBox.o Client.o TcpConnection.o \
		   Server.o CommandParser.o TitleBar.o

OBJ = $(ENGINE_OBJ) $(APP_OBJ)

# include paths
INC = -I.\ext\SDL2-2.0.12\i686-w64-mingw32\include\SDL2 \
	  -I.\ext\SDL2_net-2.0.1\i686-w64-mingw32\include\SDL2 \
	  -I.\ext\SDL2_image-2.0.5\i686-w64-mingw32\include\SDL2 \
	  -I.\ext\SDL2_ttf-2.0.15\i686-w64-mingw32\include\SDL2

# library paths and linker flags
LDFLAGS = -L.\ext\SDL2-2.0.12\i686-w64-mingw32\lib \
		  -L.\ext\SDL2_net-2.0.1\i686-w64-mingw32\lib \
		  -L.\ext\SDL2_image-2.0.5\i686-w64-mingw32\lib \
		  -L.\ext\SDL2_ttf-2.0.15\i686-w64-mingw32\lib -mwindows

# libraries
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_net

# source directories
VPATH = src src/engine src/application


all: $(OBJ)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(BIN)


.PHONY: clean

run: 
	$(BIN)

clean:
	-rm $(OBJ) $(BIN).exe
