package music;

import javax.sound.sampled.*;
import java.io.*;

public class MP3 implements Runnable
{
   private Song mp3;
   private MP3Listener listen;
   private volatile boolean running;

   
   public MP3(Song mp3, MP3Listener listen)
   {
      this.mp3 = mp3;
      this.listen = listen;
      running = true;
   }

   public void stopMP3()
   {
      running = false;
   }

   
   public void run()
   {
      play();

      listen.mp3Done();
   }


   public void play()
   {
      try
      {
         File file = new File(mp3.getMP3());
         AudioInputStream in = AudioSystem.getAudioInputStream(file);
         AudioInputStream din = null;
         AudioFormat baseFormat = in.getFormat();
         AudioFormat decodedFormat = new AudioFormat(AudioFormat.Encoding.PCM_SIGNED, baseFormat.getSampleRate(), 16, baseFormat.getChannels(), baseFormat.getChannels() * 2, baseFormat.getSampleRate(), false);
         din = AudioSystem.getAudioInputStream(decodedFormat, in);

         //play
         rawplay(decodedFormat, din);  //the main part of the thread
         in.close();
       }
       catch (Exception e)
       {
          System.out.println("Unable to play mp3.");
       }
   }

   private void rawplay(AudioFormat targetFormat, AudioInputStream din) throws IOException, LineUnavailableException
   {
      byte[] data = new byte[4096];
      SourceDataLine line = getLine(targetFormat);
      if (line != null)
      {
         //start
         line.start();
         int nBytesRead = 0, nBytesWritten = 0;

         while (nBytesRead != -1 && running)  
         {
            nBytesRead = din.read(data, 0, data.length);
            if (nBytesRead != -1)
            {
               nBytesWritten = line.write(data, 0, nBytesRead);
            }
         }

         //stop
         line.drain();
         line.stop();
         line.close();
         din.close();
      }
   }

   private SourceDataLine getLine(AudioFormat audioFormat) throws LineUnavailableException
   {
      SourceDataLine res = null;
      DataLine.Info info = new DataLine.Info(SourceDataLine.class, audioFormat);
      res = (SourceDataLine) AudioSystem.getLine(info);
      res.open(audioFormat);
      return res;
   }
}
