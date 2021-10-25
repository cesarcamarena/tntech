package music;

import java.util.Iterator;
import table.TableInterface;
import table.TableFactory;

public class Music
{
   private TableInterface<Artist, String> artists;

   public Music(String file)
   {
      artists = TableFactory.createTable(new CompareArtists(true));
      readMusic(file);
   }
   
   public Iterator<Artist> iterator()
   {
      return artists.iterator();
   }

   private void readMusic(String file_name)
   {
      util.ReadTextFile rf = new util.ReadTextFile(file_name);
      String art = rf.readLine();
      while (!rf.EOF())
      {
         String title = rf.readLine();
         System.out.println(title);
         int year = Integer.parseInt(rf.readLine());
         int rating = Integer.parseInt(rf.readLine());
         int numTracks = Integer.parseInt(rf.readLine());
         CD cd = new CD(title, art, year, rating, numTracks);

         int tracks = 1;

         while (tracks <= numTracks)
         {
            String temp = rf.readLine();
            String[] line = temp.split(",");
            String len = line[0];
            String song_title = line[1];
			   Song song = new Song(song_title, len, art, cd.getTitle(), tracks);
            cd.addSong(song);
            tracks++;
         }
		 
		   //DO THIS
         //if the artist isn't already present in the table, create a new artist and insert it

         Artist artist = artists.tableRetrieve(art);
		    
		   if (artist == null)
         {
            artist = new Artist(art);
            artists.tableInsert(artist);
         }

         try
         {
            artist.addCD(cd);
         }

         catch (MusicException me)
         {
            System.out.println("Ignoring duplicate CD.");
         }

         art = rf.readLine();
      }
	  
	  rf.close();
   }

   public static void main(String[] args)
   {
      Music mc = new Music("resources/cds.txt");
      //instantiate your GUI here

      MusicGUI mg = new MusicGUI(640, 480, mc.iterator());
   }
}