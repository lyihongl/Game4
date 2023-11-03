LIBS = -w -lmingw32 -lSDL2main -lSDL2 -DLOG_USE_COLOR -lgdi32 -lopengl32 \
			-luser32 -lkernel32 -lglu32 
INC = 	-IC:\Dev\glm -IC:\Dev\glad\include \
		-IC:\mingw64\x86_64-w64-mingw32\include -LC:\mingw64\x86_64-w64-mingw32\lib \
		-IC:\Dev\SDL2-2.0.10\x86_64-w64-mingw32\include \
		-LC:\Dev\SDL2-2.0.10\x86_64-w64-mingw32\lib \
		-IC:\Dev\glew-2.1.0\include \
		-LC:\Dev\glew-2.1.0\lib\Release\x64 \
		-IC:\Dev\inc


CXX = g++
CXXFLAGS = -std=c++17

SRC_DIR = .
INC_DIR = ./inc

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, %.o, $(SRCS))
OBJS += glad.o

RELEASE_OBJ_DIR = ./obj/release
RELEASE_OBJ = $(addprefix $(RELEASE_OBJ_DIR)/, $(OBJS))
RELEASE_FLAGS = -O3 -DNDEBUG

DEBUG_OBJ_DIR = ./obj/debug
DEBUG_OBJ = $(addprefix $(DEBUG_OBJ_DIR)/, $(OBJS))
DEBUG_FLAGS = -g -O0 -DDEBUG

OUT_DIR = ./output

TARGET = $(OUT_DIR)/Game4.exe
TARGET_DEBUG = $(OUT_DIR)/Game4Debug.exe

all: $(TARGET)

debug: $(TARGET_DEBUG)

$(TARGET): $(RELEASE_OBJ)
	$(CXX) $(RELEASE_FLAGS) $^ -o $@ $(INC) $(LIBS) 

$(RELEASE_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(RELEASE_FLAGS) -c $< -o $@

$(RELEASE_OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(RELEASE_FLAGS) $(INC) -c $< -o $@

$(RELEASE_OBJ_DIR)/render.o: $(SRC_DIR)/render.cpp
	$(CXX) $(RELEASE_FLAGS) $(INC) -c $< -o $@

$(RELEASE_OBJ_DIR)/glad.o: C:\\Dev\\glad\\src\\glad.c
	g++ $(RELEASE_FLAGS) -c C:\Dev\glad\src\glad.c -IC:\Dev\glad\include -o $@


$(TARGET_DEBUG): $(DEBUG_OBJ)
	$(CXX) $(DEBUG_FLAGS) $^ -o $@ $(INC) $(LIBS) 

$(DEBUG_OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(DEBUG_FLAGS) -c $< -o $@

$(DEBUG_OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(DEBUG_FLAGS) $(INC) -c $< -o $@

$(DEBUG_OBJ_DIR)/render.o: $(SRC_DIR)/render.cpp
	$(CXX) $(RELEASE_FLAGS) $(INC) -c $< -o $@

$(DEBUG_OBJ_DIR)/glad.o: C:\\Dev\\glad\\src\\glad.c
	g++ $(DEBUG_FLAGS) -c C:\Dev\glad\src\glad.c -IC:\Dev\glad\include -o $@

clean:
	del .\output\*.exe
	del .\obj\release\*.o
	del .\obj\debug\*.o

test:
	g++ -std=c++17 main.cpp ./obj/glad.o $(INC) $(LIBS)
# obj/main.o: main.cpp
# 	g++ -std=c++17 -c main.cpp $(INC) -o ./obj/main.o


# obj/economy.o: economy.cpp ./inc/economy.hpp
# 	g++ -c economy.cpp -o ./obj/economy.o

# obj/empire.o: empire.cpp ./inc/empire.hpp
# 	g++ -c economy.cpp -o ./obj/empire.o