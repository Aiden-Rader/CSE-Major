
public interface BoundStack<T> extends StackInterface<T>
{
	   void push(T element) throws StackOverflowException;
	   // Throws StackOverflowException if this stack is full; otherwise,
	   // places element at the top of this stack.

	   boolean isFull();
	   // Returns true if this stack is full, otherwise returns false.

}
