package music;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.dnd.*;

import gui.CenterFrame;
import gui.Drawable;
import gui.DrawPanel;
import gui.EasyGridBag;

import java.util.Iterator;

public class MusicGUI extends CenterFrame implements Drawable, ActionListener
{
	private JComboBox<Artist> cboArtists;
	private JComboBox<CD> cboCDs;
	private ManySongs lstSongs;
	private SingleSong lstSong;

	private DrawPanel draw = new DrawPanel();

	private boolean hovered = false;

	public MusicGUI(int width, int height, java.util.Iterator<Artist> it)
	{
		super(width, height, "Music Collection");
		setLayout(new BorderLayout());
		JPanel centerGrid = new JPanel();
		add(centerGrid, BorderLayout.CENTER);

		Dimension d = new Dimension(10, 17);
		lstSong = new SingleSong();
		lstSong.setPreferredSize(d);

		JPanel pnlNorth = new JPanel();
		pnlNorth.setLayout(new GridLayout(1, 2));
		cboArtists = new JComboBox<Artist>();
		cboCDs = new JComboBox<CD>();
		pnlNorth.add(cboArtists);
		pnlNorth.add(cboCDs);
		add(pnlNorth, BorderLayout.NORTH);

		//DrawPanel draw = new DrawPanel();
		draw.setDrawable(this);

		lstSongs = new ManySongs();
		lstSongs.setFont(new Font("Courier New", Font.PLAIN, 12));
		lstSongs.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		JScrollPane scrollSongs = new JScrollPane();
		scrollSongs.setPreferredSize(d);
		scrollSongs.getViewport().add(lstSongs);

		JPanel scrollPanel = new JPanel();
		scrollPanel.setLayout(new BorderLayout());
		scrollPanel.add(scrollSongs, BorderLayout.CENTER);
		scrollPanel.add(lstSong, BorderLayout.SOUTH);

		EasyGridBag easy = new EasyGridBag(1, 4, centerGrid);
		centerGrid.setLayout(easy);

		easy.fillCellWithRowColSpan(1, 2, 1, 4, GridBagConstraints.BOTH, draw);
		easy.fillCellWithRowColSpan(1, 1, 1, 1, GridBagConstraints.BOTH, scrollPanel);

		fillArtists(it);

		cboArtists.setActionCommand("artist");
		cboArtists.addActionListener(this);

		cboArtists.setSelectedIndex(0);

		cboCDs.setActionCommand("cds");
		cboCDs.setSelectedIndex(0);

		DragSource dragSource = DragSource.getDefaultDragSource();
		DragGestureRecognizer dgr = dragSource.createDefaultDragGestureRecognizer(lstSongs, DnDConstants.ACTION_COPY, lstSongs);
		DropTarget dropTarget = new DropTarget(lstSong, lstSong);

		setVisible(true);
	}

	public void fillArtists(Iterator<Artist> iterator)
	{
		while (iterator.hasNext())
		{
			cboArtists.addItem(iterator.next());
		}

		Artist artist = (Artist) cboArtists.getItemAt(0);

		fillCDs(artist.iterator());
	}

	public void fillCDs(Iterator<CD> iterator)
	{
		for (int i = cboCDs.getItemCount(); i > 0; i--)
		{
			cboCDs.removeItemAt(i - 1);
		}

		while(iterator.hasNext())
		{
			cboCDs.addItem(iterator.next());
		}
	}

	public void actionPerformed(ActionEvent e)
	{
		if (e.getActionCommand().equals("artist"))
		{
			cboCDs.removeActionListener(this);

			int index = cboArtists.getSelectedIndex();

			Artist artist = cboArtists.getItemAt(index);

			fillCDs(artist.iterator());

			lstSongs.setCD(artist.getFirstCD());

			cboCDs.addActionListener(this);
		}

		else if (e.getActionCommand().equals("cds"))
		{
			int index = cboCDs.getSelectedIndex();

			CD cd = cboCDs.getItemAt(index);

			lstSongs.setCD(cd);
		}

		repaint();
	}

	public void draw(Graphics g, int width, int height)
	{
		CD cd = cboCDs.getItemAt(cboCDs.getSelectedIndex());

		if (hovered)
		{
			cd.enableFilter();
		}

		else
		{
			cd.disableFilter();
		}

		cd.draw(g, width, height);
	}

    public void mouseClicked(int x, int y)
    {
    	CD cd = cboCDs.getItemAt(cboCDs.getSelectedIndex());

    	Image cd_image = cd.returnImage();

    	int width = draw.getSize().width;

    	int height = draw.getSize().height;

     	if (x > width - 300 && x < width - (300 - cd_image.getWidth(this)) && y > height - 300 && y < height - (300 - cd_image.getHeight(this)))
     	{
     	   hovered = true;
     	}    

     	else 
     	{
     	   hovered = false;
     	}

    }

    public void keyPressed(char key)
    {

    }
}
