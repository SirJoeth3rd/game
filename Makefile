#OBJ_NAME specifies the name of our executable
OBJ_NAME = nevergray

#OBJS specifies which files to compile as part of the project
OBJS = $(OBJ_NAME).cpp

#COMPILER_FLAGS specifies the additional compilation options we're using
#-w supresses all warnings
COMPILER_FLAGS = -w -std=c++0x

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -pthread

#This is the target that compile our executable
all: $(OBJS)
	gcc -c -std=gnu99 -o flecs.o flecs.c
	g++ -c $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME).o
	g++ -o $(OBJ_NAME) $(OBJ_NAME).o flecs.o $(COMPILER_FLAGS) $(LINKER_FLAGS)
