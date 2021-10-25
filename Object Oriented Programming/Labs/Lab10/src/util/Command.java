package util;

//used to create a new class that defines a task
public interface Command<E> 
{
	public void execute(E item);
}
