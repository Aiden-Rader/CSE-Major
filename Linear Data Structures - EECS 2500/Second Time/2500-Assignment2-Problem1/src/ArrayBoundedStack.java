/* Homework Assignment 2 -- problem 1
 * Aiden Rader
 * 
 * EECS 2500 Linear Data Structures
 * Dr.Kishwar Ahmed
 * 01/30/2023
 */

public class ArrayBoundedStack<T> implements StackInterface<T> 
{
	  protected final int DEFCAP = 100; // default capacity
	  protected T[] elements;           // holds stack elements
	  protected int topIndex = -1;      // index of top element in stack

	@SuppressWarnings("unchecked")
	public ArrayBoundedStack() 
	  {
	    elements = (T[]) new Object[DEFCAP];
	  }

	@SuppressWarnings("unchecked")
	public ArrayBoundedStack(int maxSize) 
	  {
	    elements = (T[]) new Object[maxSize];
	  }

	  public void push(T element)
	  // Throws StackOverflowException if this stack is full,
	  // otherwise places element at the top of this stack.
	  {      
	    if (isFull())
	      throw new StackOverflowException("Push attempted on a full stack.");
	    else
	    {
	      topIndex++;
	      elements[topIndex] = element;
	    }
	  }

	  public void pop()
	  // Throws StackUnderflowException if this stack is empty,
	  // otherwise removes top element from this stack.
	  {                  
	    if (isEmpty())//Referring to method below
	    	throw new StackUnderflowException("Pop attempted on an empty stack.");
	    
	    else
	    {
	      elements[topIndex] = null;
	      topIndex--;
	    }
	  }

	  public T top()
	  // Throws StackUnderflowException if this stack is empty,
	  // otherwise returns top element of this stack.
	  {                 
	    T topOfStack = null;
	    if (isEmpty())
	      throw new StackUnderflowException("Top attempted on an empty stack.");
	    else
	      topOfStack = elements[topIndex];
	    return topOfStack;
	  }

	  public boolean isEmpty()
	  // Returns true if this stack is empty, otherwise returns false.
	  {              
	    return (topIndex == -1); 
	  }

	  public boolean isFull()
	  // Returns true if this stack is full, otherwise returns false.
	  {              
	    return (topIndex == (elements.length - 1));
	  }
	  
	  
	  //This is where the methods/classes/constructors are being placed
	  
	  
	  public String toString() 
	  
	  //unsure how the toString works, Email Lab TA about this 
	  {
		  String print = new String();
		  if (isEmpty())
		  {
			  print = "\nThe stack is empty";
		  }
		  else
		  {
			  print = ("There are " + size() + " elements in the stack:");
			  
			  for (int i = topIndex; i >= 0; i--)
				  print = print + "\n\t" + elements[i];  
		  }
		  return print;
	  }
	  
	  public int size()
	  {
		return topIndex + 1;
		  
	  }
	  
	  public void popSome(int countValue)
	  {
		  if(size()<countValue) throw new StackUnderflowException ("Less number of elements in stack.");
		  while(countValue>0)
		  {
			  elements[topIndex]=null;
			  topIndex--;
			  countValue--;
		  }
	  }
	  
	  public boolean swapStart()
	  {
		  if (size()<2)
			  return false;
		  
		  T topOfStack = null;
		  topOfStack=elements[topIndex];
		  elements[topIndex]=elements[topIndex-1];
		  elements[topIndex-1]=topOfStack;
		  return true;
	  }
	  
	  public T poptop()
	  {
		  if(topIndex==-1)
			  throw new StackUnderflowException("Top attempted on an empty stack.");
		  else
		  {
			  T topI=null;
			  topI=elements[topIndex--];
			  return topI;
		  }
	  }
}