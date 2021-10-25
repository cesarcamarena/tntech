#include "Face.h"
#include <math.h>

Face::Face()
{
   vertices = new ListArray<Vertex>();
   sze = 0;
}

Face::~Face()
{
   delete vertices;
}

void Face::addVertex(Vertex* vertex)
{
   if (sze < 3)
   {
      vertices->add(sze + 1, vertex);
      sze++;
   }
}

Vertex* Face::getVertex(int index)
{
   return vertices->get(index);
}

void Face::render(Pixel* px, Matrix* transform)
{
   Vertex* v1 = getVertex(1);
   Vertex* v2 = getVertex(2);
   Vertex* v3 = getVertex(3);

   //put vertices into window coordinates (directly from local coordinates)
   v1 = v1->multiply(transform);
   v2 = v2->multiply(transform);
   v3 = v3->multiply(transform);

   Vertex* temp = v1->homogenize();
   delete v1;
   v1 = temp;
   temp = v2->homogenize();
   delete v2;
   v2 = temp;
   temp = v3->homogenize();
   delete v3;
   v3 = temp;

   //draw the wireframe of the triangle
   drawLine(px, v1, v2);
   drawLine(px, v2, v3);
   drawLine(px, v3, v1);

   delete v1;
   delete v2;
   delete v3;
}

void Face::drawLine(Pixel* px, Vertex* first, Vertex* second)
{
   double x0, x1, y0, y1;
   x0 = first->getX();
   y0 = first->getY();
   x1 = second->getX();
   y1 = second->getY();
   int stepx = 1;
   int stepy = 1;

   double r0, g0, b0, r1, g1, b1;
   double denom;

   r0 = first->getRed() * 255;
   g0 = first->getGreen() * 255;
   b0 = first->getBlue() * 255;

   r1 = second->getRed() * 255;
   g1 = second->getGreen() * 255;
   b1 = second->getBlue() * 255;

   int dx = ((int) (x1 + 0.5)) - ((int) (x0 + 0.5)); 
   int dy = ((int) (y1 + 0.5)) - ((int) (y0 + 0.5));

   int dr = ((int) (r1 + 0.5)) - ((int) (r0 + 0.5)); 
   int dg = ((int) (g1 + 0.5)) - ((int) (g0 + 0.5)); 
   int db = ((int) (b1 + 0.5)) - ((int) (b0 + 0.5)); 

   if (dx < 0)
   {
      dx = -1*dx;
      stepx = -1;
   }
   if (dy < 0)
   {
      dy = -1*dy;
      stepy = -1;
   }

   dx = dx << 1;  //left shift to double dx and dy
   dy = dy << 1;

   if (dx > dy)  //need to determine if x will be incremeted or y will be incremented
   {
      denom = 1.0/(x1 - x0);

      dr = (int) (dr*denom);
      dg = (int) (dg*denom);
      db = (int) (db*denom);

      int r = (int) (r0 + 0.5);
      int g = (int) (g0 + 0.5);
      int b = (int) (b0 + 0.5);

      if ((dr < 0 && r1 > r0) || (dr > 0 && r0 > r1))
      {
         r = (int) (r1 + 0.5);
      }
      if ((dg < 0 && g1 > g0) || (dg > 0 && g0 > g1))
      {
         g = (int) (g1 + 0.5);
      }
      if ((db < 0 && b1 > b0) || (db > 0 && b0 > b1))
      {
         b = (int) (b1 + 0.5);
      }

      int x0i = (int) (x0 + 0.5);  //0.5 added to handle rounding correctly
      int x1i = (int) (x1 + 0.5);
      int yi = (int) (y0 + 0.5); 

      int fraction = dy - (dx >> 1);

      int x = x0i;
      Color color(r/225.0, g/255.0, b/255.0);
      px->drawPixel(x0i, yi, color);

      while (x != x1i)
      {
         if (fraction >= 0)
         {
            yi = yi + stepy;
            fraction = fraction - dx;
         }
         fraction = fraction + dy;

         r = r + dr;
         g = g + dg;
         b = b + db;

         x = x + stepx;

         Color color(r/225.0, g/255.0, b/255.0);
         px->drawPixel(x, yi, color);
      }
   }

   else
   {
      denom = 1.0/(y1 - y0);

      dr = (int) (dr*denom);
      dg = (int) (dg*denom);
      db = (int) (db*denom);

      int r = (int) (r0 + 0.5);
      int g = (int) (g0 + 0.5);
      int b = (int) (b0 + 0.5);

      if ((dr < 0 && r1 > r0) || (dr > 0 && r0 > r1))
      {
         r = (int) (r1 + 0.5);
      }
      if ((dg < 0 && g1 > g0) || (dg > 0 && g0 > g1))
      {
         g = (int) (g1 + 0.5);
      }
      if ((db < 0 && b1 > b0) || (db > 0 && b0 > b1))
      {
         b = (int) (b1 + 0.5);
      }

      int y0i = (int) (y0 + 0.5);
      int y1i = (int) (y1 + 0.5);
      int xi = (int) (x0 + 0.5);

      int fraction = dx - (dy >> 1);

      int y = y0i;
      Color color(r/255.0, g/255.0, b/225.0);
      px->drawPixel(xi, y0i, color);

      while (y != y1i)
      {
         if (fraction >= 0)
         {
            xi = xi + stepx;
            fraction = fraction - dy;
         }
         fraction = fraction + dx;

         r = r + dr;
         g = g + dg;
         b = b + db;

         y = y + stepy;

         Color color(r/255.0, g/255.0, b/225.0);
         px->drawPixel(xi, y, color);
      }
   }
}

/*
void Face::drawLine(Pixel* px, Vertex* first, Vertex* second)
{
   //vertices have been transformed to window coordinates, so just draw the appropriate pixels

   double x0, y0, x1, y1;
   double r0, g0, b0, r1, g1, b1;
   double denom, dx, dy, dr, dg, db;
   double m, r, g, b;

   x0 = first->getX();
   y0 = first->getY();
   x1 = second->getX();
   y1 = second->getY();

   //single point, don't render
   //if (fabs(x1 - x0) < 0.001 && fabs(y1 - y0) < .001)  
   //{
      //return;
   //}

   if (fabs(x1 - x0) < 0.001)
   {
      m = 1.5; //loop over y in case of infinite slope
   }
   else
   {
      m = (y1 - y0)/(x1 - x0);
   }

   if (fabs(m) < 1)  //need to determine if x will be incremeted or y will be incremented
   {
      //slope is less than one so we will loop over x values, calculating y values

      if (x0 > x1)  //need to swap x and y values so that x1 > x0
      {
         Vertex* temp = first;
         first = second;
         second = temp;
      }

      x0 = first->getX();
      y0 = first->getY();
      x1 = second->getX();
      y1 = second->getY();

      r0 = first->getRed();
      g0 = first->getGreen();
      b0 = first->getBlue();
      r1 = second->getRed();
      g1 = second->getGreen();
      b1 = second->getBlue();

      denom = 1.0/(x1 - x0);
      dy = (y1 - y0)*denom;
      dr = (r1 - r0)*denom;
      dg = (g1 - g0)*denom;
      db = (b1 - b0)*denom;

      double y = y0;
      r = r0;
      g = g0;
      b = b0;

      for (int x = (static_cast<int>(x0 + 0.5)); x <= (static_cast<int>(x1 + 0.5)); x++)
      {
         Color color(r, g, b);
         px->drawPixel(x, static_cast<int>(y + 0.5), color);

         y = y + dy;
         r = r + dr;
         g = g + dg;
         b = b + db;
      }
   }

   else
   {
      //slope is greater than one so we will loop over y values, calculating x values

      if (y0 > y1)  //make sure that y1 > y0
      {
         Vertex* temp = first;
         first = second;
         second = temp;
      }

      x0 = first->getX();
      y0 = first->getY();
      x1 = second->getX();
      y1 = second->getY();

      r0 = first->getRed();
      g0 = first->getGreen();
      b0 = first->getBlue();
      r1 = second->getRed();
      g1 = second->getGreen();
      b1 = second->getBlue();

      denom = 1.0/(y1 - y0);
      dx = (x1 - x0)*denom;
      dr = (r1 - r0)*denom;
      dg = (g1 - g0)*denom;
      db = (b1 - b0)*denom;

      double x = x0;
      r = r0;
      g = g0;
      b = b0;

      for (int y = static_cast<int>(y0 + 0.5); y <= static_cast<int>(y1 + 0.5); y++)
      {
         Color color(r, g, b);
         px->drawPixel(static_cast<int>(x + 0.5), y, color);

         x = x + dx;
         r = r + dr;
         g = g + dg;
         b = b + db;
      }
   }
}
*/

void Face::printFace()
{
   for (int i = 1; i <= sze; i++)
   {
      Vertex* vertex = getVertex(i);
      vertex->displayVertex();
   }
}
