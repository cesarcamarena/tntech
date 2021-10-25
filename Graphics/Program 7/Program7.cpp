#include "Window.h"

int main(int argc, char** argv)
{
   const char* title = "Textures";
   Window window(argc, argv, 800, 600, 450, 250, title);
   window.show();
   return 0;
}
