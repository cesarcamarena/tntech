package util;

public class GameWriteFileVisitor implements GameVisitor
{
	private String file_name;
	public GameWriteFileVisitor(String fn)
	{
		file_name = fn;
	}
	
	public void visit(brass.BrassGame brass_game)
	{
		org.jdom2.output.XMLOutputter text = new org.jdom2.output.XMLOutputter(org.jdom2.output.Format.getPrettyFormat());
		org.jdom2.Document doc = brass_game.writeGameXML();
		java.io.PrintWriter pw = null;
		try
		{
			java.io.FileWriter fw = new java.io.FileWriter(file_name);
			java.io.BufferedWriter bw = new java.io.BufferedWriter(fw);
			pw = new java.io.PrintWriter(bw);
			text.output(doc, pw);
		}
		catch(java.io.IOException ioe) 
		{
			System.out.println(ioe.getMessage());
		}
	}
}
