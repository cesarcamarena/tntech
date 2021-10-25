package util;

public class StackLinked<T>
{
   private Node<T> top;
   private int size;

   public StackLinked() 
   {
      top = null; 
      size = 0;
   } 
  
   public boolean isEmpty() 
   {
      return size == 0;
   }  

   public int size()
   {
      return size;
   }

   public void popAll() 
   {
      top = null;
      size = 0;
   }  

   public T peek()
   {
	   if (isEmpty()) return null;
	   return top.getItem();
   }  

   public void push(T item)
   {
      Node<T> node = new Node<T>(item);
      node.setNext(top);
      top = node;
      size++;
   }  

   public T pop()
   {
	   if (isEmpty()) return null;

         T temp = top.getItem();
         top = top.getNext();
         size--;
         return temp;
   } 
}
