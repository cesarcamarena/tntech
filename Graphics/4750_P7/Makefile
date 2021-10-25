AutomatedMakefile = am
CC = g++

INC_DIRS = -I$(PROJECT_PATH)/CSC1310/include
LIB_DIRS = -L$(PROJECT_PATH)/CSC1310
LIBS = -lCSC1310 -lfreeglut -lopengl32

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

FILES = AffineTransforms.o Color.o Vector.o Vertex.o Pixel.o Face.o BasicObject.o Picture.o Window.o Scene.o InstanceObject.o DeleteObject.o Node.o TransformNode.o Light.o Texture.o Program1.o
all: 4750_P7

4750_P7: 		$(FILES)
			$(LINK) P7.exe $(FILES) $(LIBS)

AffineTransforms.o:	AffineTransforms.h AffineTransforms.cpp
			$(COMPILE) AffineTransforms.cpp

Color.o:		Color.h Color.cpp
			$(COMPILE) Color.cpp
			
Vector.o:		Vector.h Vector.cpp
			$(COMPILE) Vector.cpp	

Vertex.o:		Vertex.h Vertex.cpp
			$(COMPILE) Vertex.cpp

Pixel.o:		Pixel.h Pixel.cpp
			$(COMPILE) Pixel.cpp

Face.o:			Face.h Face.cpp
			$(COMPILE) Face.cpp

BasicObject.o:		BasicObject.h BasicObject.cpp
			$(COMPILE) BasicObject.cpp

Picture.o:		Picture.h Picture.cpp
			$(COMPILE) Picture.cpp

Window.o:		Window.h Window.cpp
			$(COMPILE) Window.cpp
			
Scene.o:		Scene.h Scene.cpp
			$(COMPILE) Scene.cpp
			
InstanceObject.o:	InstanceObject.h InstanceObject.cpp
			$(COMPILE) InstanceObject.cpp
			
DeleteObject.o:	DeleteObject.h DeleteObject.cpp
			$(COMPILE) DeleteObject.cpp
			
Node.o:		Node.h Node.cpp
			$(COMPILE) Node.cpp
			
TransformNode.o:		TransformNode.h TransformNode.cpp
			$(COMPILE) TransformNode.cpp	

Light.o:		Light.h Light.cpp
			$(COMPILE) Light.cpp	

Texture.o:		Texture.h Texture.cpp
			$(COMPILE) Texture.cpp				

Program1.o:		Program1.cpp
			$(COMPILE) Program1.cpp
