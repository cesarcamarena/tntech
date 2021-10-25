AutomatedMakefile = am
CC = g++

CSC1310_PATH = $(PROJECT_PATH)/CSC1310

INC_DIRS = -I$(PROJECT_PATH) -I$(CSC1310_PATH)/include
LIB_DIRS = -L$(PROJECT_PATH) -L$(CSC1310_PATH) 
LIBS = -lCSC1310 -lglew32 -lfreeglut -lglu32 -lopengl32

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = ReadObject.o Texture.o AffineTransforms.o Color.o Light.o Vertex.o Vector.o BasicObject.o InstanceObject.o Node.o TransformNode.o Scene.o Window.o DeleteObject.o Main.o Picture.o
all: 4750_GLSL

4750_GLSL: 		$(FILES)
			$(LINK) Main.exe $(FILES) $(LIBS)

Texture.o:		Texture.h Texture.cpp
			$(COMPILE) Texture.cpp

ReadObject.o:		ReadObject.h ReadObject.cpp
			$(COMPILE) ReadObject.cpp

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Vector.o:		Vector.h Vector.cpp
			$(COMPILE) Vector.cpp

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

Light.o:		Light.h Light.cpp
			$(COMPILE) Light.cpp

Main.o:			Main.cpp
			$(COMPILE) Main.cpp



