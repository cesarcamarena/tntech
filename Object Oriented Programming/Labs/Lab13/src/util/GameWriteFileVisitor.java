package util;

//DO THIS set up for visitor design pattern
public class GameWriteFileVisitor implements GameVisitor
{
	private String file_name;
	public GameWriteFileVisitor(String fn)
	{
		file_name = fn;
	}
	
	public void visit(brass.BrassGame brass_game)
	{
		//DO THIS
		//insert try-catch required for compilation
		
		//org.jdom2.JDOMException
		//java.io.IOException
		
		org.jdom2.output.XMLOutputter text = new org.jdom2.output.XMLOutputter(org.jdom2.output.Format.getPrettyFormat());
		org.jdom2.Document doc = brass_game.writeGameXML();
		java.io.PrintWriter pw = null;
		
		java.io.FileWriter fw = new java.io.FileWriter(file_name);
		java.io.BufferedWriter bw = new java.io.BufferedWriter(fw);
		pw = new java.io.PrintWriter(bw);
		text.output(doc, pw);
	}
}
