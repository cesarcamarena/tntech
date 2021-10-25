package util;

//DO THIS set up for visitor design pattern
public class GameReadFileVisitor implements GameVisitor
{
	private String file_name;
	public GameReadFileVisitor(String fn)
	{
		file_name = fn;
	}
	
	//tailor the communication to the game according to the methods
	//available in the game (Brass requires XML)
	//handle exceptions so that if an exception occurs, the save or load simply does not occur
	public void visit(brass.BrassGame brass_game)
	{
		//DO THIS
		//insert try-catch required for compilation
		//if the file is not present, also catch the exception and return
		
		java.io.File file = new java.io.File(file_name);
      
		org.jdom2.input.SAXBuilder saxb = new org.jdom2.input.SAXBuilder();
        org.jdom2.Document doc = null;
		
		doc = saxb.build(file);
		brass_game.readGameXML(doc);
		
	}
}
