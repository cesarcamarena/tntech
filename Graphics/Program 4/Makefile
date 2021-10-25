AutomatedMakefile = am
CC = g++

CSC1310_PATH = $(PROJECT_PATH)/CSC1310

INC_DIRS = -I$(PROJECT_PATH) -I$(CSC1310_PATH)/include
LIB_DIRS = -L$(PROJECT_PATH) -L$(CSC1310_PATH)
LIBS = -lCSC1310 -lfreeglut -lopengl32

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = AffineTransforms.o Color.o Vertex.o Pixel.o Face.o BasicObject.o InstanceObject.o Node.o TransformNode.o Scene.o Window.o DeleteObject.o Program4.o Picture.o Vector.o
all: 4750_P3

4750_P3: 		$(FILES)
			$(LINK) P4.exe $(FILES) $(LIBS)

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Pixel.o:		Pixel.h Pixel.cpp
			$(COMPILE) Pixel.cpp

Face.o:			Face.h Face.cpp
			$(COMPILE) Face.cpp

BasicObject.o:		BasicObject.h BasicObject.cpp
			$(COMPILE) BasicObject.cpp

InstanceObject.o:	InstanceObject.h InstanceObject.cpp
			$(COMPILE) InstanceObject.cpp

Scene.o:		Scene.h Scene.cpp
			$(COMPILE) Scene.cpp

Picture.o:		Picture.h Picture.cpp
			$(COMPILE) Picture.cpp

Window.o:		Window.h Window.cpp
			$(COMPILE) Window.cpp

DeleteObject.o:		DeleteObject.h DeleteObject.cpp
			$(COMPILE) DeleteObject.cpp

Node.o:			Node.h Node.cpp
			$(COMPILE) Node.cpp

TransformNode.o:	TransformNode.h TransformNode.cpp
			$(COMPILE) TransformNode.cpp

Program4.o:		Program4.cpp
			$(COMPILE) Program4.cpp

Vector.o:		Vector.h Vector.cpp
			$(COMPILE) Vector.cpp