#include <GL/glew.h>
#include <GL/glut.h>
#include "Window.h"
#include "Picture.h"
#include "ReadObject.h"
#include <iostream>
//#include <stdlib.h>
using namespace std;

void Window::staticDisplay()
{
   int w, h;
   w = glutGet(GLUT_WINDOW_WIDTH);
   h = glutGet(GLUT_WINDOW_HEIGHT);
   reshape(w, h);
}

void Window::display(int w, int h)  //callback for window drawing
{
   Picture pict;
   pict.render(w, h);

   glutSwapBuffers();  //for double buffering
   glFlush();  //forces completion of drawing
}

//callback for window resizing
void Window::reshape(int w, int h)  
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   display(w, h);  //need this here to make the callback work correctly
}

void Window::show()
{
   glutMainLoop();  //show everything
}

Window::~Window(){}

Window::Window(int argc, char** argv, int width, int height, int xLoc, int yLoc, const char* title)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  //use rgb color and double buffering 
   
   glutInitWindowSize(width, height);

   glutInitWindowPosition(xLoc, yLoc);  //place the window near the center of the screen
   glutCreateWindow(title);

   glClearColor(0.0, 0.0, 0.0, 1.0);  //background color is black

   glutDisplayFunc(Window::staticDisplay);  //set the repaint callback function (redraws after window has been resized)
   glutReshapeFunc(Window::reshape);        //set the reshape callback function (redraws while window is resized)

   //don't show back facing polygons
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

   //enable z-buffering
   glEnable(GL_DEPTH_TEST);

   //enable lighting
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);  //makes sure that normals have unit length (slow)

   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);


   //GLEW

   //compile, link, and use shader programs
   GLenum err = glewInit();
   cout << "using glew version " << glewGetString(GLEW_VERSION) << endl;

   const char* fileName1 = "vertex_shader_NormalMap.txt";
   //const char* fileName1 = "vertex_shader_Phong.txt";
   //char* fileName = "vertex_shader_Texture.txt";
   GLchar* str_v = getText(fileName1);

   int status;  //compilation status

   GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertShader, 1, (const GLchar**)&str_v, NULL);
   glCompileShader(vertShader);
   glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      //from Fidel Abella
      /*
      cout << "vertex shader compilation failed" << endl;
      GLint logLen;
      glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);
      if (logLen > 0)
      {
         char* log = (char*) malloc(logLen);
         GLsizei written;
         glGetShaderInfoLog(vertShader, logLen, &written, log);
         fprintf(stderr, "Shader log:\n%s", log);
         free(log);
      }
      */
   }
   else
   {
      cout << "vertex shader compilation successful" << endl;
   }

   const char* fileName2 = "fragment_shader_NormalMap.txt";
   //const char* fileName2 = "fragment_shader_Phong.txt";  
   //fileName = "fragment_shader_Texture.txt";
   GLchar* str_f = getText(fileName2);

   GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragShader, 1, (const GLchar**)&str_f, NULL);
   glCompileShader(fragShader);
   glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      cout << "fragment shader compilation failed" << endl;
   }
   else
   {
      cout << "fragment shader compilation successful" << endl;
   }

   const char* fileName3 = "geometry_shader_NormalMap.txt";  
   //const char* fileName3 = "geometry_shader_Phong.txt";  
   GLchar* str_g = getText(fileName3);

   GLuint geomShader = glCreateShader(GL_GEOMETRY_SHADER_EXT);  
   glShaderSource(geomShader, 1, (const GLchar**)&str_g, NULL);
   glCompileShader(geomShader);
   glGetShaderiv(geomShader, GL_COMPILE_STATUS, &status);
   if (status == GL_FALSE)
   { 
      cout << "geometry shader compilation failed" << endl;
   }
   else
   {
      cout << "geometry shader compilation successful" << endl;
   }

   GLuint program = glCreateProgram();

   glAttachShader(program, vertShader);
   glAttachShader(program, geomShader);
   glAttachShader(program, fragShader);

   glProgramParameteriEXT(program, GL_GEOMETRY_INPUT_TYPE_EXT, GL_TRIANGLES);
   glProgramParameteriEXT(program, GL_GEOMETRY_OUTPUT_TYPE_EXT, GL_TRIANGLE_STRIP);
   glProgramParameteriEXT(program, GL_GEOMETRY_VERTICES_OUT_EXT, 3); 

   glLinkProgram(program);

   GLint linkStatus;
   glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
   if (linkStatus == 1)
   { 
      cout << "all shaders linked" << endl;
   }

   glUseProgram(program);

   GLint loc = glGetUniformLocation(program, "image_1");
   glUniform1i(loc, 2);

   loc = glGetUniformLocation(program, "image_2");
   glUniform1i(loc, 3);

   delete[] str_v;
   delete[] str_f;
   delete[] str_g;
}
