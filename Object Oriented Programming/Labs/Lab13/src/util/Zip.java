package util;

import java.io.*;
import java.util.zip.*;

public class Zip 
{
	private byte[] data;
	private int buffer_size;
	private static Zip zip = new Zip(2048);
		
	private Zip(int buffer)
	{
		data = new byte[buffer];
		buffer_size = buffer;
	}
	
	public static Zip getZip()
	{
		return zip;
	}
	
	public void unZip(String zip_file_name) throws Exception
	{
		BufferedOutputStream dest = null;
         FileInputStream fis = new FileInputStream(zip_file_name);
         CheckedInputStream checksum = new CheckedInputStream(fis, new Adler32());
         ZipInputStream zis = new ZipInputStream(new BufferedInputStream(checksum));
		 
         ZipEntry entry = zis.getNextEntry();
         while(entry != null) 
		 {
            System.out.println("Extracting: " + entry);
			
            FileOutputStream fos = new FileOutputStream(entry.getName());
            dest = new BufferedOutputStream(fos, buffer_size);
			int count = zis.read(data, 0, buffer_size);
            while (count != -1) 
			{
               dest.write(data, 0, count);
			   count = zis.read(data, 0, buffer_size);
            }
            dest.flush();
            dest.close();
			
			entry = zis.getNextEntry();
         }
         zis.close();
		 
         System.out.println("Checksum: "+checksum.getChecksum().getValue());
	}
	
	public void zipFile( String file_name, String output_zip_file_name) throws Exception
	{
         BufferedInputStream origin = null;
         FileOutputStream dest = new FileOutputStream(output_zip_file_name);
         CheckedOutputStream checksum = new CheckedOutputStream(dest, new Adler32());
         ZipOutputStream out = new ZipOutputStream(new BufferedOutputStream(checksum));

            System.out.println("Adding: " + file_name);
			FileInputStream fi = new FileInputStream(file_name);
			origin = new BufferedInputStream(fi, buffer_size);
			
			//the String passed to ZipEntry cannot have path information
            ZipEntry entry = new ZipEntry(file_name);
            out.putNextEntry(entry);
			
			int count = origin.read(data, 0, buffer_size);
            while(count != -1) 
			{
               out.write(data, 0, count);
			   count = origin.read(data, 0, buffer_size);
            }
            origin.close();

         out.close();
		 
         System.out.println("checksum: "+checksum.getChecksum().getValue());
   }
} 
