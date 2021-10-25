#include "Face.h"
#include "Vertex.h"

#include "ListArray.h"
using CSC1310::ListArray;

#include "ListArrayIterator.h"
using CSC1310::ListArrayIterator;

#include "ReadFile.h"
using CSC1310::ReadFile;

#include "WriteFile.h"
using CSC1310::WriteFile;

#include "Tokens.h"
using CSC1310::Tokens;

#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

double* computeST(Vertex* v)
{
	double* st = new double[2];

	double PI = 3.1415927;

	double x = v->getX();
	double y = v->getY();
	double z = v->getZ();

	double p_squared = x*x + y*y + z*z;

	double p = sqrt(p_squared);

	double theta = acos(y/p);

	double phi = atan(x/z);

	double t = 1 - (theta/PI);

	double s = phi/(2*PI);

	if (x >= 0 && z < 0)
	{
		s += 0.5;
	}

	else if (x < 0 && z < 0)
	{
		s += 0.5;
	}

	else if (x < 0 && z >= 0)
	{
		s += 1.0;
	}

	else if (x >= 0 && z >= 0)
	{
		//do nothing? still need to handle the wedge of death
	}



	st[0] = s;
	st[1] = t;

	return st;
}

int getFaceIndex(String* face_indices)
{
	Tokens* tokens  = new Tokens(face_indices, '/');
	int num_tokens = tokens->getNumTokens();

	String* face_index = tokens->getToken(0);
	int index = face_index->a_to_i();

	//the rest of the tokens are not used, but need to be deleted
	for (int i = 0; i < num_tokens; i++)
	{
		String* temp = tokens->getToken(i);
		delete temp;
	}

	delete tokens;
	return index;
}

int main ()
{
	ListArray<Vertex>* vertices = new ListArray<Vertex>();

	ListArray<Face>* faces = new ListArray<Face>();

	ReadFile* rf = new ReadFile("sphere.txt");

	WriteFile* wf = new WriteFile("sphere_texture.txt");

	double x, y, z;

	String* v = new String("v");
	String* f = new String("f");

	String* line = rf->readLine();
	wf->writeLine(line);
	while (!rf->eof())
	{
		Tokens* tokens = new Tokens(line, ' ');
		int num_tokens = tokens->getNumTokens();
		String* token = tokens->getToken(0);

		if (token->compare(v) == 0)
		{
			delete token;

			token = tokens->getToken(1);
			x = token->a_to_f();
			delete token;

			token = tokens->getToken(2);
			y = token->a_to_f();
			delete token;

			token = tokens->getToken(3);
			z = token->a_to_f();
			delete token;

			Vertex* vertex = new Vertex(x, y, z);
			vertices->add(vertex);
		}

		else if (token->compare(f) == 0)
		{
			delete token;

			String* face_indices = tokens->getToken(1);
			int index1 = getFaceIndex(face_indices);
			delete face_indices;

			face_indices = tokens->getToken(2);
			int index2 = getFaceIndex(face_indices);
			delete face_indices;

			face_indices = tokens->getToken(3);
			int index3 = getFaceIndex(face_indices);
			delete face_indices;

			Face* face = new Face();

			Vertex* vertex1 = vertices->get(index1);
			Vertex* vertex2 = vertices->get(index2);
			Vertex* vertex3 = vertices->get(index3);

			face->addVertex(vertex1);
			//vertex1->addFace(face);
			face->addVertex(vertex2);
			//vertex2->addFace(face);
			face->addVertex(vertex3);
			//vertex3->addFace(face);

			faces->add(face);
		}

		else
		{
			for (int i = 0; i < num_tokens; i++)
			{
				String* temp = tokens->getToken(i);
				delete temp;
			}
		}

		delete line;
		delete tokens;
		line = rf->readLine();
		wf->writeLine(line);
	}

	ListArrayIterator<Face>* iter = faces->iterator();
	while (iter->hasNext())
	{
		Face* face = iter->next();
		Vertex* v1 = face->getVertex(1);
		Vertex* v2 = face->getVertex(2);
		Vertex* v3 = face->getVertex(3);

		double* st1 = computeST(v1);

		double* st2 = computeST(v2);

		double* st3 = computeST(v3);

		double s1 = st1[0];
		double s2 = st2[0];
		double s3 = st3[0];

		double t1 = st1[1];
		double t2 = st2[1];
		double t3 = st3[1];

		double max = s1;

		if (max < s2)
		{
			max = s2;
		}

		if (max < s3)
		{
			max = s3;
		}

		if (max > 0.8)
		{
			if (s1 < 0.3)
			{
				s1 += 1.0;
			}

			if (s2 < 0.3)
			{
				s2 += 1.0;
			}

			if (s3 < 0.3)
			{
				s3 += 1.0;
			}
		}

		cout << s1 << " " << t1 << " " << s2 << " " << t2 << " " << s3 << " " << t3 << endl;

		string s1_str = std::to_string(s1);
		string t1_str = std::to_string(t1);

		string s2_str = std::to_string(s2);
		string t2_str = std::to_string(t2);

		string s3_str = std::to_string(s3);
		string t3_str = std::to_string(t3);

		string line = "vt " + s1_str + " " + t1_str + " " + s2_str + " " + t2_str + " " + s3_str + " " + t3_str;

		int n = line.length();

		// declaring character array 
    	char char_array[n + 1]; 
  
   		// copying the contents of the 
  		// string to char array 
    	strcpy(char_array, line.c_str());

    	String* string = new String(char_array);

		wf->writeLine(string);

		delete string;
	}

	delete line;
	delete v;
	delete f;
	delete rf;

	return 0;
}