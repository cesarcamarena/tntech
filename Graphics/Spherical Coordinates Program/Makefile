AutomatedMakefile = am
CC = g++ -std=c++11

CSC1310_PATH = $(PROJECT_PATH)/CSC1310

INC_DIRS = -I$(PROJECT_PATH) -I$(CSC1310_PATH)/include
LIB_DIRS = -L$(PROJECT_PATH) -L$(CSC1310_PATH)
LIBS = -lCSC1310 -lfreeglut -lopengl32

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = Vertex.o Face.o program.o Color.o Vector.o Pixel.o Light.o
all: 4750_P3

4750_P3: 		$(FILES)
			$(LINK) program.exe $(FILES) $(LIBS)

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Face.o:			Face.h Face.cpp
			$(COMPILE) Face.cpp

program.o:		program.cpp
			$(COMPILE) program.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Vector.o:		Vector.h Vector.cpp
			$(COMPILE) Vector.cpp

Pixel.o:		Pixel.h Pixel.cpp
			$(COMPILE) Pixel.cpp

Light.o:		Light.h Light.cpp
			$(COMPILE) Light.cpp