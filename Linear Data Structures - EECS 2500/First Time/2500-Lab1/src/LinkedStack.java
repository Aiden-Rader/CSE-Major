public class LinkedStack<T> implements StackInterface<T>
{
	protected LLNode<T> top;  //reference to the top of this stack

	  public LinkedStack()
	  {
	    // constructor – there’s no data to fill in; just make the stack
	    // be empty by ensuring that the top reference refers to nothing

	    top = null;
	  }

	  public void push(T element)
	  {
		//Put a new element on the top of the stack:
	    LLNode<T> newNode = new LLNode<T>(element); //Create new node to hold the element. 
	    newNode.setLink(top); 						//Make new node point where top used to.
	    top = newNode; 								//Make top point to new node
	  }

	public void pop() throws StackUnderflowException
	{
	    //If stack not empty, removes the object from top of the stack
	    //If stack IS empty, throws StackUnderflowException
		
	    if (isEmpty())
	    	throw new StackUnderflowException("Attempt to pop empty stack");  //If stack empty, throw underflow exception. 
	    else 
	       top = top.getLink(); //Make top point to what the first node currently points to
	}
	
	public T top() throws StackUnderflowException
	{
		   // If stack is NOT empty, returns the object from the top of the
		   // stack. If stack IS empty, throws StackUnderflowException

		   if (isEmpty()) 
		       throw new StackUnderflowException("Attempted top() on empty stack");
		   else 
		       return top.getInfo();
	}
	
	public boolean isEmpty()
	{
		   return (top == null); // returns true if the stack is empty; false if it is not empty
	}
}
