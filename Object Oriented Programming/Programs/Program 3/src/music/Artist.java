package music;

import java.util.Iterator;
import table.TableInterface;
import table.TableFactory;

public class Artist
{
	private String name;
	private TableInterface<CD, String> cds;
	
	public Artist(String name)
	{
		this.name = name;
		cds = TableFactory.createTable(new CompareCDTitles(true));
	}

	public String getArtist()
	{
		return name;
	}

	public int getSize()
	{
		return cds.tableSize();
	}

	public boolean isEmpty()
	{
		return cds.tableIsEmpty();
	}

	public Iterator<CD> iterator()
	{
		return cds.iterator();
	}

	public void addCD(CD cd) throws MusicException
	{
		try
		{
			cds.tableInsert(cd);
		}

		catch (table.TableException e)
		{
			throw new MusicException();
		}
	}

	public CD getFirstCD()
	{
		Iterator<CD> iterator = iterator();
		return iterator.next();
	}

	public String toString()
	{
		return name;
	}

}