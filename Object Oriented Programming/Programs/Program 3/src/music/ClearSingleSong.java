package music;

public class ClearSingleSong implements Runnable
{
	private SingleSong single_song;

	public ClearSingleSong(SingleSong single_song)
	{
		this.single_song = single_song;
	}

	public void run()
	{
		single_song.clear();
	}
}