#include "Face.h"
#include <math.h>
#include <iostream>
using namespace std;

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

Vector* Face::getNormal(Vertex* v1, Vertex* v2, Vertex* v3)
{
   Vector* v2minusv1 = v2->subtract(v1);
   Vector* v3minusv1 = v3->subtract(v1);
   Vector* temp = v2minusv1->cross(v3minusv1);
   Vector* n = temp->normalize();
   delete v2minusv1;
   delete v3minusv1;
   delete temp;
   return n;
}

void Face::render(Pixel* px, Matrix* transform, Color* diffuse, Matrix* zbuffer)
{
   Vertex* v1 = getVertex(1);
   Vertex* v2 = getVertex(2);
   Vertex* v3 = getVertex(3);

   //put vertices into window coordinates 
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
   
   //back face culling
   Vector* n = getNormal(v1, v2, v3);

   if (n->getZ() < 0)  //discard positive normals due to windowing transform
   {
      //set the diffuse color from the instance object material
      /*
      v1->setRed(diffuse->getRed());
      v2->setRed(diffuse->getRed());
      v3->setRed(diffuse->getRed());

      v1->setGreen(diffuse->getGreen());
      v2->setGreen(diffuse->getGreen());
      v3->setGreen(diffuse->getGreen());

      v1->setBlue(diffuse->getBlue());
      v2->setBlue(diffuse->getBlue());
      v3->setBlue(diffuse->getBlue());
      */


      //check color interpolation
      v1->setRed(1);
      v2->setRed(0);
      v3->setRed(0);

      v1->setGreen(0);
      v2->setGreen(1);
      v3->setGreen(0);

      v1->setBlue(0);
      v2->setBlue(0);
      v3->setBlue(1);


      drawTriangle(v1, v2, v3, zbuffer, px);
   }

   delete v1;
   delete v2;
   delete v3;
   delete n;
}

void Face::drawTriangle(Vertex* first, Vertex* second, Vertex* third, Matrix* zbuffer, Pixel* px)
{
   double x0, x1, x2, y0, y1, y2, z0, z1, z2;
   x0 = first->getX();   //point a
   y0 = first->getY();  
   z0 = first->getZ();
   x1 = second->getX();  //point b
   y1 = second->getY();
   z1 = second->getZ();
   x2 = third->getX();   //point c
   y2 = third->getY();
   z2 = third->getZ();

   double r0, g0, b0, r1, g1, b1, r2, g2, b2;

   r0 = first->getRed();
   g0 = first->getGreen();
   b0 = first->getBlue();
   r1 = second->getRed();
   g1 = second->getGreen();
   b1 = second->getBlue();
   r2 = third->getRed();
   g2 = third->getGreen();
   b2 = third->getBlue();

   //find the bounding rectangle
   double xmax = x0;
   double xmin = x0;
   double ymax = y0;
   double ymin = y0;

   if (x1 > xmax)
   {
      xmax = x1;
   }
   if (x1 < xmin)
   {
      xmin = x1;
   }
   if (x2 > xmax)
   {
      xmax = x2;
   }
   if (x2 < xmin)
   {
      xmin = x2;
   }

   if (y1 > ymax)
   {
      ymax = y1;
   }
   if (y1 < ymin)
   {
      ymin = y1;
   }
   if (y2 > ymax)
   {
      ymax = y2;
   }
   if (y2 < ymin)
   {
      ymin = y2;
   }

   //the following clipping based on an idea from Roger Shelton
   //I need the clipping planes in screen coords and I can get them from the z buffer
   double maxX = zbuffer->getNumCols() - 1 + 0.5;  //use these values to clip in x and y
   double maxY = zbuffer->getNumRows() - 1 + 0.5;

   double minX = -0.5;
   double minY = -0.5;

   //check to see if the face is completely clipped out
   if (xmax < minX)  
   {
      return;
   }
   if (xmin > maxX)
   {
      return;
   }
   if (ymax < minY)
   {
      return;
   }
   if (ymin > maxY)
   {
      return;
   }

   //set clipping
   if (xmin < minX)
   {
      xmin = minX;
   }
   if (xmax > maxX)
   {
      xmax = maxX;
   }
   if (ymin < minY)
   {
      ymin = minY;
   }
   if (ymax > maxY)
   {
      ymax = maxY;
   }

   double bx  = x1 - x0;
   double by  = y1 - y0;
   double cx  = x2 - x0;
   double cy  = y2 - y0;

   double dr1 = r1 - r0;
   double dr2 = r2 - r0;
   double dg1 = g1 - g0;
   double dg2 = g2 - g0;
   double db1 = b1 - b0;
   double db2 = b2 - b0;

   double dz1 = z1 - z0;
   double dz2 = z2 - z0;

   double denom = 1.0/((double)(cy*bx - by*cx));

   double bx_d = bx*denom;
   double by_d = by*denom;
   double cx_d = cx*denom;
   double cy_d = cy*denom;

   double beta_incr_x  =  cy_d;
   double gamma_incr_x = -by_d;

   double beta_incr_y  = -cx_d;
   double gamma_incr_y =  bx_d;

   double x_start = ((int) xmin - x0);
   double y_start = ((int) ymin - y0);

   double beta_start  = cy_d*x_start - cx_d*y_start;  
   double gamma_start = bx_d*y_start - by_d*x_start;   

   double r_start  = r0 + beta_start*dr1 + gamma_start*dr2;
   double g_start  = g0 + beta_start*dg1 + gamma_start*dg2;
   double b_start  = b0 + beta_start*db1 + gamma_start*db2;
   double z_start  = z0 + beta_start*dz1 + gamma_start*dz2;

   double r_incr_x = beta_incr_x*dr1 + gamma_incr_x*dr2;
   double g_incr_x = beta_incr_x*dg1 + gamma_incr_x*dg2;
   double b_incr_x = beta_incr_x*db1 + gamma_incr_x*db2;
   double z_incr_x = beta_incr_x*dz1 + gamma_incr_x*dz2;

   double r_incr_y = beta_incr_y*dr1 + gamma_incr_y*dr2;
   double g_incr_y = beta_incr_y*dg1 + gamma_incr_y*dg2;
   double b_incr_y = beta_incr_y*db1 + gamma_incr_y*db2;
   double z_incr_y = beta_incr_y*dz1 + gamma_incr_y*dz2;

   //loop over the bounding rectangle for the triangle only
   for (int x = (int) xmin; x <= (int) xmax; x++) 
   {             
      //reset beta and gamma for the next loop over y
      double beta  = beta_start;
      double gamma = gamma_start;

      double r = r_start;
      double g = g_start;
      double b = b_start;
      double z = z_start;

      for (int y = (int) ymin; y <= (int) ymax; y++)
      {
         //inside the triangle?
         if (beta <= 1 && beta >= 0 && gamma <= 1 && gamma >= 0 && beta + gamma <= 1 )  
         {
            //cout << z << endl;
            if (z > zbuffer->getElement(y + 1, x + 1) && z < 1)
            {
               zbuffer->setElement(y + 1, x + 1, z);
               Color color(r, g, b);
               px->drawPixel(x, y, color);
            }
         }

         beta  += beta_incr_y;
         gamma += gamma_incr_y;

         r += r_incr_y;
         g += g_incr_y;
         b += b_incr_y;

         z += z_incr_y;
      }

      //incremental changes (efficient)
      beta_start  += beta_incr_x;
      gamma_start += gamma_incr_x;

      r_start += r_incr_x;
      g_start += g_incr_x;
      b_start += b_incr_x;

      z_start += z_incr_x;
   }
}

void Face::displayFace()
{
   for (int i = 1; i <= sze; i++)
   {
      Vertex* vertex = getVertex(i);
      vertex->displayVertex();
   }
}
