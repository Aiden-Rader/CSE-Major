
public interface StackInterface<String> 
{
	void push(String element) throws StackOverflowException;
	// Throws StackOverflowException if this stack is full,
	// otherwise places element at the top of this stack.

	void pop() throws StackUnderflowException;
	// Throws StackUnderflowException if this stack is empty,
	// otherwise removes top element from this stack.

	String top() throws StackUnderflowException;
	// Throws StackUnderflowException if this stack is empty,
	// otherwise returns top element of this stack.

	boolean isEmpty();
	// Returns true if this stack is empty, otherwise returns false.

	boolean isFull();
	// Returns true if this stack is full, otherwise returns false.
	
	void popSome(int countValue);
	
	String poptop();
}

