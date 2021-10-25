package util;

//used by the class that contains the collection
public interface Execute<E>
{
   public void execute(Command<E> command);
}


