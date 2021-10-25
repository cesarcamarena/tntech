package util;

public interface FindCommand<E, T> extends Command<E>
{
	public java.util.List<T> getList();
}
