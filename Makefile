LIBS = -w -lmingw32 -lSDL2main -lSDL2 -DLOG_USE_COLOR -lgdi32 -lopengl32 \
			-luser32 -lkernel32 -lglu32 
INC = 	-IC:\Dev\glm\glm -IC:\Dev\glad\include \
		-IC:\mingw64\x86_64-w64-mingw32\include -LC:\mingw64\x86_64-w64-mingw32\lib \
		-IC:\Dev\SDL2-2.0.10\x86_64-w64-mingw32\include \
		-LC:\Dev\SDL2-2.0.10\x86_64-w64-mingw32\lib \
		-IC:\Dev\glew-2.1.0\include \
		-LC:\Dev\glew-2.1.0\lib\Release\x64 \
		-IC:\Dev\inc

CXX = g++
CPPFLAGS = -std=c++17

SRC_DIR = .
INC_DIR = ./inc
OBJ_DIR = ./obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS += obj/glad.o

TARGET = Game4.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $@ $(INC) $(LIBS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR)/glad.o: C:\\Dev\\glad\\src\\glad.c
	g++ -c C:\Dev\glad\src\glad.c -IC:\Dev\glad\include -o ./obj/glad.o

clean:
	del Game4.exe
	del .\obj\*.o

test:
	g++ -std=c++17 main.cpp ./obj/glad.o $(INC) $(LIBS)
# obj/main.o: main.cpp
# 	g++ -std=c++17 -c main.cpp $(INC) -o ./obj/main.o


# obj/economy.o: economy.cpp ./inc/economy.hpp
# 	g++ -c economy.cpp -o ./obj/economy.o

# obj/empire.o: empire.cpp ./inc/empire.hpp
# 	g++ -c economy.cpp -o ./obj/empire.o