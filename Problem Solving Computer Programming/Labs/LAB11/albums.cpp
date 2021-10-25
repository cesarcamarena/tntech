/*
	Program Name: albums.cpp
	Author: Cesar Camarena
	Date: 11/16/2016
	Purpose: lab11
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

struct Album
{
	string title;
	string artist;
	string genre;
	int year;
	int numSongs;
	float starRate;		//represents the number of stars (between 1 and 5)
						//that this album received
};

int enterAlbums(Album*);
void printAlbums(Album*, int);
void printLowestRating(Album*, int);
void printFiveStar(Album*, int);

const int SIZE = 1000;

int main()
{
	int numAlbums;
	
	Album myMusic[SIZE];
	numAlbums = enterAlbums(myMusic);
	printAlbums(myMusic, numAlbums);
	printLowestRating(myMusic, numAlbums);
	printFiveStar(myMusic, numAlbums);
	
	return 0;
}

/*
	Function Title: enterAlbums
	Function Purpose: Enters the data from the allmymusic.txt into the myMusic struct array
*/
int enterAlbums(Album* myMusic)
{
	ifstream musicFile;
	string temp;
	int numAlbums = 0;
	
	musicFile.open("albums.txt");
	if(!musicFile)
	{
		cout << "\nI am sorry. The file was unable to be opened!" << endl;
		exit(EXIT_FAILURE);
	}
	
	else
	{
		getline(musicFile, temp);  //attempt one read
		while(!musicFile.eof())
		{
			myMusic[numAlbums].title = temp;
			getline(musicFile, myMusic[numAlbums].artist);
			getline(musicFile, myMusic[numAlbums].genre);
			musicFile >> myMusic[numAlbums].year;
			musicFile >> myMusic[numAlbums].numSongs;
			musicFile >> myMusic[numAlbums].starRate;
			
			numAlbums++;
			musicFile.ignore();
			getline(musicFile, temp);  //read the next album's title
		}
		
		cout << "\nThe file albums.txt was opened." << endl;
		cout << "There were " << numAlbums << " albums read into the program!" << endl;
		
		musicFile.close();
		
		return numAlbums;
	}
}

/*
	Function Title: printAlbums
	Function Purpose: To display the data that was entered into the myMusic struct array.
					  It displays the album title, artist, genre, year released, number of songs,
					  and it's star rating.
*/
void printAlbums(Album* myMusic, int numAlbums)
{
	ofstream allMusicFile;
	
	allMusicFile.open("allmymusic.txt");
	
	for(int x = 0; x < numAlbums; x++)
	{
		allMusicFile << "----------------------------------- ";
		allMusicFile << "ALBUM " << (x + 1) << " -----------------------------------" << endl;
		allMusicFile << setw(20) << right << "Album Title:  " << myMusic[x].title << endl;
		allMusicFile << setw(20) << right << "Artist:  " << myMusic[x].artist << endl;
		allMusicFile << setw(20) << right << "Genre:  " << myMusic[x].genre << endl;
		allMusicFile << setw(20) << right << "Year Released:  " << myMusic[x].year << endl;
		allMusicFile << setw(20) << right << "Number of Songs:  " << myMusic[x].numSongs << endl;
		allMusicFile << setw(20) << right << "Rating:  ";
		
		if(myMusic[x].starRate == .5)
		{
			allMusicFile << "1/2";
		}
		
		for(int count = 0; count < myMusic[x].starRate; count++)
		{
			allMusicFile << "* ";
			
		}
		
		if(myMusic[x].starRate == 1.5 || myMusic[x].starRate == 2.5 || myMusic[x].starRate == 3.5 || myMusic[x].starRate == 4.5)
		{
			allMusicFile << "and 1/2";
		}
		allMusicFile << endl;
		
	}
	
	allMusicFile.close();
	
	cout << "\nAll of your albums have been printed to allmymusic.txt!\n" << endl;
}

/*
	Function Title: printLowestRating
	Function Purpose: To display which album has the lowest star rating, and advises the
					  user to probably get rid of it.
*/
void printLowestRating(Album* myMusic, int numAlbums)
{
	string lowestAlbum = myMusic[0].title;
	float lowestRate = myMusic[0].starRate;
	
	for(int x = 0; x < numAlbums; x++)
	{
		if(myMusic[x].starRate < lowestRate)
		{
			lowestAlbum = myMusic[x].title;
			lowestRate = myMusic[x].starRate;
		}
	}
	
	cout << "You should probably get rid of" << endl;
	cout << lowestAlbum << endl;
	cout << "because it has the lowest rating of " << lowestRate << " stars!\n" << endl;
}

/*
	Function Title: printFiveStar
	Function Purpose: To display which albums received five stars, and displays which
					  artist it is from.
*/
void printFiveStar(Album* myMusic, int numAlbums)
{
	cout << "The following albums all have five stars!!" << endl;
	
	for(int x = 0; x < numAlbums; x++)
	{
		if(myMusic[x].starRate == 5)
		{
			cout << myMusic[x].title << " by " << myMusic[x].artist << endl;
		}
	}
}