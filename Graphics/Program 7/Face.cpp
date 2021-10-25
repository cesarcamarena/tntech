#include "Face.h"
#include <math.h>

#include <iostream>
using namespace std;

Face::Face()
{
   vertices = new ListArray<Vertex>();
   sze = 0;
   sCoords = new double[3];
   tCoords = new double[3];
}

Face::~Face()
{
   delete vertices;
   delete[] sCoords;
   delete[] tCoords;
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

void Face::setSCoords(double s1, double s2, double s3)
{
   sCoords[0] = s1;
   sCoords[1] = s2;
   sCoords[2] = s3;
}

void Face::setTCoords(double t1, double t2, double t3)
{
   tCoords[0] = t1;
   tCoords[1] = t2;
   tCoords[2] = t3;
}

double Face::getS(int index)
{
   return sCoords[index];
}

double Face::getT(int index)
{
   return tCoords[index];
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

void Face::render(Pixel* px, Matrix* sceneTransform, Matrix* instanceTransform, Vertex* eye, Light* light, Color* diffuse, Color* ambient, double atten, double shine, Matrix* zbuffer, unsigned char* tColors, Texture* tex)
{
   Vertex* v1 = getVertex(1);
   Vertex* v2 = getVertex(2);
   Vertex* v3 = getVertex(3);

   //must average the normals before transformations and transform the normals separately
   Matrix* inverse = instanceTransform->inverse();
   Matrix* normalTransform = inverse->transpose();

   Vector* n1 = averageNormals(v1, normalTransform);
   Vector* n2 = averageNormals(v2, normalTransform);
   Vector* n3 = averageNormals(v3, normalTransform);
   delete inverse;
   delete normalTransform;

   //put vertices into world coordinates for shading calculation
   v1 = v1->multiply(instanceTransform);
   v2 = v2->multiply(instanceTransform);
   v3 = v3->multiply(instanceTransform);
   v1->setNormal(n1);
   v2->setNormal(n2);
   v3->setNormal(n3);

   calculateColor(v1, eye, light, diffuse, ambient, atten, shine);
   calculateColor(v2, eye, light, diffuse, ambient, atten, shine);
   calculateColor(v3, eye, light, diffuse, ambient, atten, shine);

   //the vertex methods copy the colors over to the new vertices
   Vertex* temp = v1->multiply(sceneTransform);
   delete v1;
   v1 = temp;
   temp = v2->multiply(sceneTransform);
   delete v2;
   v2 = temp;
   temp = v3->multiply(sceneTransform);
   delete v3;
   v3 = temp;

   temp = v1->homogenize();
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
      drawTriangle(v1, v2, v3, zbuffer, px, tColors, tex);
   }
   delete n;

   delete v1;
   delete v2;
   delete v3;
}

//this method must be in the Face class due to the forward reference to Face from Vertex.h
Vector* Face::averageNormals(Vertex* v, Matrix* normalTransform)
{
   ListArray<Face>* faces = v->getFaces();

   Vector* n = new Vector(0, 0, 0);
   int size = faces->size();

   Vector** normals = new Vector*[size];
   Vertex** vertices = new Vertex*[3];

   for (int i = 0; i < size; i++)
   {
      Face* face = faces->get(i + 1);
      for (int j = 0; j < 3; j++)
      {
         vertices[j] = face->getVertex(j + 1);
      }

      Vector* a = vertices[1]->subtract(vertices[0]);
      Vector* b = vertices[2]->subtract(vertices[0]);
      Vector* temp = a->cross(b);
      normals[i] = new Vector(temp->getX(), temp->getY(), temp->getZ());

      delete a;
      delete b;
      delete temp;
   }

   double x = 0;
   double y = 0;
   double z = 0;

   for (int i = 0; i < size; i++)
   {
      x += normals[i]->getX();
      y += normals[i]->getY();
      z += normals[i]->getZ();
   }

   n->setX(x/size);
   n->setY(y/size);
   n->setZ(z/size);

   Vector* temp = n->normalize();
   delete n;
   n = temp;

   for (int i = 0; i < size; i++)
   {
      delete normals[i];
   }

   delete[] normals;
   delete[] vertices;

   temp = n->multiply(normalTransform);
   delete n;
   n = temp;

   return n;
}

void Face::calculateColor(Vertex* vertex, Vertex* eye, Light* light, Color* diffuse, Color* ambient, double linearAttenuation, double shininess)
{
   //eye is the camera position and is needed for the specular component
   Vector* n = vertex->getNormal();
   n = n->normalize();

   //set the color of the vertex to black
   vertex->setRed(0);
   vertex->setBlue(0);
   vertex->setGreen(0);

   //set the ambient color first
   //mulitply ambient light color by ambient material color
   double r = ambient->getRed();
   double g = ambient->getGreen();
   double b = ambient->getBlue();

   //assume a single point light source for now
   for (int i = 1; i <= 1; i++)  //loop over all point light sources in the scene
   {
      double rd, gd, bd;
      double rs, gs, bs;

      double dotd;
      double attenuation;

      Color* color = light->getColor();        //don't delete (done inside light)
      Vertex* location = light->getLocation(); //don't delete (done inside light)

      Vector* l = location->subtract(vertex);  //vector that points from the point on the surface to the light source
      //note that l has not been normalized, so it measures the distance from the surface to the light source

      attenuation = l->dot(l);  //this is the length squared (before normalization of the l vector)
      attenuation = sqrt(attenuation);  //attenuation is now equal to the distance to the light source (linear attenuation)
      attenuation = linearAttenuation*attenuation; //reduce attenuation

      Vector* temp = l->normalize();  //now we can normalize l
      delete l;
      l = temp;
      dotd = l->dot(n);  //diffuse component

      //calculate the reflected vector direction
      Vector* refl = new Vector(0, 0, 0);
      refl->setX(2*(dotd)*(n->getX()) - (l->getX()));
      refl->setY(2*(dotd)*(n->getY()) - (l->getY()));
      refl->setZ(2*(dotd)*(n->getZ()) - (l->getZ()));

      Vector* tmp = eye->subtract(vertex);  //v is the vector from the surface to the camera
      Vector* v = tmp->normalize();
      delete tmp;

      if (dotd < 0)
      {
         dotd = 0;
      }

      double dots = 0;  //will contain the specular component
      if (dotd > 0) //can only have a specular component if l.n > 0
      {
         double specular = refl->dot(v);
         if (specular > 0)
         {
            dots = pow(specular, shininess);  //specular component
         }
      }

      dotd = dotd/attenuation;    //assume modified linear attenuation for diffuse component
      dots = dots/attenuation;    //assume modified linear attenuation for specular component

/*
      //light source color times material color times diffuse component
      rd = color->getRed() * diffuse->getRed()*dotd;  
      gd = color->getGreen() * diffuse->getGreen()*dotd;
      bd = color->getBlue() * diffuse->getBlue()*dotd;

      //for the specular component, just use the light source color times the specular component
      rs = color->getRed() * dots;
      gs = color->getGreen() * dots;
      bs = color->getBlue() * dots;

      r = r + rd + rs;  //sum diffuse and specular terms for all lights
      g = g + gd + gs; 
      b = b + bd + bs; 
*/

      r = dotd;
      g = dotd;
      b = dotd;

      delete l;
      delete v;
      delete refl;
   }

   //the color class will clamp the colors if necessary
   vertex->setRed(r);
   vertex->setGreen(g);
   vertex->setBlue(b);
   delete n;
}

void Face::drawTriangle(Vertex* first, Vertex* second, Vertex* third, Matrix* zbuffer, Pixel* px, unsigned char* tColors, Texture* tex)
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

   double h0, h1, h2, inverseh0, inverseh1, inverseh2;

   h0 = first->getH();
   h1 = second->getH();
   h2 = third->getH();
   inverseh0 = 1/h0;
   inverseh1 = 1/h1;
   inverseh2 = 1/h2;

   double r0, g0, b0, r1, g1, b1, r2, g2, b2;

   r0 = first->getRed() * inverseh0;
   g0 = first->getGreen() * inverseh0;
   b0 = first->getBlue() * inverseh0;
   r1 = second->getRed() * inverseh1;
   g1 = second->getGreen() * inverseh1;
   b1 = second->getBlue() * inverseh1;
   r2 = third->getRed() * inverseh2;
   g2 = third->getGreen() * inverseh2;
   b2 = third->getBlue() * inverseh2;

   double s0, s1, s2, t0, t1, t2;

   s0 = getS(0) * inverseh0;  
   t0 = getT(0) * inverseh0;  
   s1 = getS(1) * inverseh1;  
   t1 = getT(1) * inverseh1;
   s2 = getS(2) * inverseh2;   
   t2 = getT(2) * inverseh2;

   int tWidth = tex->getWidth(); 
   int tHeight = tex->getHeight();

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

   double dh1 = inverseh1 - inverseh0;
   double dh2 = inverseh2 - inverseh0;

   double ds1 = s1 - s0;
   double ds2 = s2 - s0;
   double dt1 = t1 - t0;
   double dt2 = t2 - t0;

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
   double h_start  = inverseh0 + beta_start*dh1 + gamma_start*dh2;
   double s_start  = s0 + beta_start*ds1 + gamma_start*ds2;
   double t_start  = t0 + beta_start*dt1 + gamma_start*dt2;

   double r_incr_x = beta_incr_x*dr1 + gamma_incr_x*dr2;
   double g_incr_x = beta_incr_x*dg1 + gamma_incr_x*dg2;
   double b_incr_x = beta_incr_x*db1 + gamma_incr_x*db2;
   double z_incr_x = beta_incr_x*dz1 + gamma_incr_x*dz2;
   double h_incr_x = beta_incr_x*dh1 + gamma_incr_x*dh2;
   double s_incr_x = beta_incr_x*ds1 + gamma_incr_x*ds2;
   double t_incr_x = beta_incr_x*dt1 + gamma_incr_x*dt2;

   double r_incr_y = beta_incr_y*dr1 + gamma_incr_y*dr2;
   double g_incr_y = beta_incr_y*dg1 + gamma_incr_y*dg2;
   double b_incr_y = beta_incr_y*db1 + gamma_incr_y*db2;
   double z_incr_y = beta_incr_y*dz1 + gamma_incr_y*dz2;
   double h_incr_y = beta_incr_y*dh1 + gamma_incr_y*dh2;
   double s_incr_y = beta_incr_y*ds1 + gamma_incr_y*ds2;
   double t_incr_y = beta_incr_y*dt1 + gamma_incr_y*dt2;

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
      double h = h_start;
      double s = s_start;
      double t = t_start;

      for (int y = (int) ymin; y <= (int) ymax; y++)
      {
         //inside the triangle?
         if (beta <= 1 && beta >= 0 && gamma <= 1 && gamma >= 0 && beta + gamma <= 1 )  
         {
            if (z > zbuffer->getElement(y + 1, x + 1) && z < 1)
            {
               double inverseh = 1.0/h;
               double s_over_h = s * inverseh;
               double t_over_h = t * inverseh;

               int stexel = ((int) (tWidth * s_over_h)) % tWidth;
               int ttexel = ((int) (tHeight * t_over_h)) % tHeight;
               ttexel = tHeight - ttexel - 1;  //y increases downward

               //colors are stored r,g,b,r,g,b...
               //compute the index for the above pixel center
               int index = (ttexel*tWidth + stexel) * 3;

               //pull the colors out for the given index
               double r_tex = (tColors[index + 0]/255.0) * (r * inverseh); 
               double g_tex = (tColors[index + 1]/255.0) * (g * inverseh);
               double b_tex = (tColors[index + 2]/255.0) * (b * inverseh);

               zbuffer->setElement(y + 1, x + 1, z);
               Color color(r_tex, g_tex, b_tex);
               px->drawPixel(x, y, color);
            }
         }

         beta  += beta_incr_y;
         gamma += gamma_incr_y;

         r += r_incr_y;
         g += g_incr_y;
         b += b_incr_y;

         z += z_incr_y;
         h += h_incr_y;

         s += s_incr_y;
         t += t_incr_y;
      }

      //incremental changes (efficient)
      beta_start  += beta_incr_x;
      gamma_start += gamma_incr_x;

      r_start += r_incr_x;
      g_start += g_incr_x;
      b_start += b_incr_x;

      z_start += z_incr_x;
      h_start += h_incr_x;

      s_start += s_incr_x;
      t_start += t_incr_x;
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
