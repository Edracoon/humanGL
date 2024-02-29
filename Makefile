CXX = clang++ -std=c++11 -w

APP_INCLUDES:= -I./src/EngineGL/vendors/GLFW -framework Cocoa -framework OpenGL -framework IOKit
APP_LINKER:= -L./src/EngineGL/vendors/GLFW/lib -lglfw3

CPP_FILES = ${wildcard src/*.cpp} \
			${wildcard src/EngineGL/vendors/*.cpp} \
			${wildcard src/EngineGL/*.cpp} \
			${wildcard src/EngineGL/Texture/*.cpp} \
			${wildcard src/EngineGL/Model/*.cpp} \
			${wildcard src/EngineGL/Shader/*.cpp}

C_FILES = ./src/EngineGL/vendors/glad/glad.c

TARGET = scop

all:
	$(CXX) $(C_FILES) $(CPP_FILES) $(APP_INCLUDES) $(APP_LINKER) -o scop

clean:
	rm -rf scop

.PHONY: all clean
