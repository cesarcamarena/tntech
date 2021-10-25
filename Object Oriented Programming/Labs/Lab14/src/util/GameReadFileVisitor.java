package util;

public class GameReadFileVisitor implements GameVisitor
{
	private String file_name;
	public GameReadFileVisitor(String fn)
	{
		file_name = fn;
	}
	
	//tailor the communication to the game according to the methods
	//available in the game (Brass requires XML)
	public void visit(brass.BrassGame brass_game)
	{
		java.io.File file = new java.io.File(file_name);
      
		org.jdom2.input.SAXBuilder saxb = new org.jdom2.input.SAXBuilder();
        org.jdom2.Document doc = null;
		
		try
		{
			doc = saxb.build(file);
			brass_game.readGameXML(doc);
		}
		catch(org.jdom2.JDOMException jdome) 
		{
			System.out.println(jdome.getMessage());
		}
		catch(java.io.IOException jdome) 
		{
			System.out.println(jdome.getMessage());
		}
	}
}
