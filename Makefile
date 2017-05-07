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
INC = -IC:\dev\include\SDL\32

# library paths and linker flags
LDFLAGS = -LC:\dev\lib\SDL\32 -mwindows

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
