#include "ListArray.h"
#include "ListArrayIterator.h"
#include "Face.h"
#include <math.h>

Face::Face()
{
	vertices = new ListArray<Vertex>();
}

Face::~Face()
{
	ListArrayIterator<Vertex>* iter = vertices->iterator();
	while (iter->hasNext())
	{
		delete iter->next();
	}

	delete iter;
	delete vertices;
}

void Face::addVertex(Vertex* v)
{
	if (vertices->size() > 3)
	{
		return;
	}

	vertices->add(v);
}

ListArray<Vertex>* Face::getVertices()
{
	return vertices;
}

void Face::render(Pixel* p, Matrix* m)
{
	ListArray<Vertex>* newVertices = new ListArray<Vertex>();
	ListArrayIterator<Vertex>* iter = vertices->iterator();

	while(iter->hasNext())
	{
		Vertex* v = iter->next();
		Vertex* newVertex = v->multiply(m);
		newVertices->add(newVertex);
	}

	renderDDA(p, newVertices->get(1), newVertices->get(3));
	renderDDA(p, newVertices->get(3), newVertices->get(2));
	renderDDA(p, newVertices->get(2), newVertices->get(1));

	//renderBresenham(p, newVertices->get(1), newVertices->get(3));
	//renderBresenham(p, newVertices->get(3), newVertices->get(2));
	//renderBresenham(p, newVertices->get(2), newVertices->get(1));

	delete newVertices;
	delete iter;
}

void Face::renderBresenham(Pixel* px, Vertex* first, Vertex* second)
{
   Color color(255.0, 0, 0);

   //vertices have been transformed to window coordinates, so just draw the appropriate pixels
   double x0 = first->getX();
   double y0 = first->getY();
   double x1 = second->getX();
   double y1 = second->getY();

   int step_x = +1;
   int step_y = +1;

   if (x0 > x1)
   {
      step_x = -1;
   }

   if (y0 > y1)
   {
      step_y = -1;
   }

   //assume the slope is a rational number, so dx and dy are integers
   double dx_temp = x1 - x0;
   double dy_temp = y1 - y0;
   int dx = static_cast<int> (dx_temp + 0.5);
   int dy = static_cast<int> (dy_temp + 0.5);
   if (dx_temp < 0) dx = static_cast<int> (dx_temp - 0.5);
   if (dy_temp < 0) dy = static_cast<int> (dy_temp - 0.5);

   if (abs(dx) >= abs(dy))  //need to determine if x will be incremeted or y will be incremented
   {
      //store the sign in dy, the numerator
      if (dx < 0)
      {
         dx = -1*dx;
         dy = -1*dy;
      }

      //slope is less than one so we will loop over x values, calculating y values
      int x_start = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_start = static_cast<int>(x0 - 0.5);
      }

      int x_end = static_cast<int>(x1 + 0.5);
      if (x1 < 0)
      {
         x_end = static_cast<int>(x1 - 0.5);
      }

      int y_i = static_cast<int>(y0 + 0.5);
      if (y0 < 0)  //if y is negative
      {
         y_i = static_cast<int>(y0 - 0.5);
      }
 
      //set initial fraction to 0.5 (some error here) and then multiply fraction and slope through by 2*dx
      int fraction = dx;  //last thing to do is to subtract 2*dx so that the comparisons are with 0
      int m_new = 2*dy;
      int f_new = 2*dx;

      while(x_start != x_end)
      {
         px->drawPixel(x_start, y_i, color);

         x_start = x_start + step_x;
         fraction = fraction + abs(m_new);  //I can simplify further if the slope is always positive

         if (fraction > f_new)
         {
            fraction = fraction - f_new;
            //y_i = y_i + step_x;
            y_i = y_i + step_y;
         }
/*
         else if (fraction < 0)
         {
            fraction = fraction + f_new;
            y_i = y_i - step_x;
         }
*/
      }
   }

   else
   {
      //store the sign in dx, the numerator
      if (dy < 0)
      {
         dx = -1*dx;
         dy = -1*dy;
      }

      int y_start = static_cast<int>(y0 + 0.5);
      if (y0 < 0)
      {
         y_start = static_cast<int>(y0 - 0.5);
      }

      int y_end = static_cast<int>(y1 + 0.5);
      if (y1 < 0)
      {
         y_end = static_cast<int>(y1 - 0.5);
      }

      int x_i = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_i = static_cast<int>(x0 - 0.5);
      }
 
      //multiply fraction through by 2*dx everywhere
      int fraction = dy;
      int m_new = 2*dx;
      int f_new = 2*dy;

      while(y_start != y_end)
      {
         px->drawPixel(x_i, y_start, color);

         y_start = y_start + step_y;
         fraction = fraction + abs(m_new);

         if (fraction > 2*dy)
         {
            fraction = fraction - f_new;
            //x_i = x_i + step_y;
            x_i = x_i + step_x;
         }
/*
         else if (fraction < 0)
         {
            fraction = fraction + f_new;
            x_i = x_i - step_y;
         }
*/
      }
   }
}

void Face::renderDDA(Pixel* px, Vertex* first, Vertex* second)
{
   Color color(0, 0, 255.0);

   //vertices have been transformed to window coordinates, so just draw the appropriate pixels
   double x0 = first->getX();
   double y0 = first->getY();
   double x1 = second->getX();
   double y1 = second->getY();

   double m;

   int step_x = +1;
   int step_y = +1;

   if (x0 > x1)
   {
      step_x = -1;
   }

   if (y0 > y1)
   {
      step_y = -1;
   }

   m = 1000.0;
   if (fabs(x1 - x0) > 0.00001)
   {
      m = (y1 - y0)/(x1 - x0);
   }

   if (fabs(m) <= 1)  //need to determine if x will be incremeted or y will be incremented
   {
      //slope is less than one so we will loop over x values, calculating y values

      int x_start = static_cast<int>(x0 + 0.5);
      if (x0 < 0)
      {
         x_start = static_cast<int>(x0 - 0.5);
      }

      int x_end = static_cast<int>(x1 + 0.5);
      if (x1 < 0)
      {
         x_end = static_cast<int>(x1 - 0.5);
      }

      double y_intercept = y1 - m*x1;
      double y = m*x_start + y_intercept;

      int y_i = static_cast<int>(y + 0.5);
      if (y < 0)  //if y is negative
      {
         y_i = static_cast<int>(y - 0.5);
      }

      double fraction = (y - y_i) + 0.5;

      while(x_start != x_end)
      {
         px->drawPixel(x_start, y_i, color);

         x_start = x_start + step_x;
         fraction = fraction + m;

         if (fraction > 1.0)
         {
            fraction = fraction - 1.0;
            y_i = y_i + step_x;
         }

         else if (fraction < 0.0)
         {
            fraction = fraction + 1.0;
            y_i = y_i - step_x;
         }
      }
   }

   else
   {
      //slope is greater than one so we will loop over y values, calculating x values
      m = (x1 - x0)/(y1 - y0);

      int y_start = static_cast<int>(y0 + 0.5);
      if (y0 < 0)
      {
         y_start = static_cast<int>(y0 - 0.5);
      }

      int y_end = static_cast<int>(y1 + 0.5);
      if (y1 < 0)
      {
         y_end = static_cast<int>(y1 - 0.5);
      }

      double x_intercept = x1 - m*y1;
      double x = m*y_start + x_intercept;

      int x_i = static_cast<int>(x + 0.5);
      if (x < 0)  //if x is negative
      {
         x_i = static_cast<int>(x - 0.5);
      }

      double fraction = (x - x_i) + 0.5;

      while (y_start != y_end)
      {
         px->drawPixel(x_i, y_start, color);

         y_start = y_start + step_y;
         fraction = fraction + m;

         if (fraction > 1.0)
         {
            fraction = fraction - 1.0;
            x_i = x_i + step_y;
         }

         else if (fraction < 0.0)
         {
            fraction = fraction + 1.0;
            x_i = x_i - step_y;
         }
      }
   }
}