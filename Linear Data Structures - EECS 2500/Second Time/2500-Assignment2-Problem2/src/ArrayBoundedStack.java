/* Homework Assignment 2 -- problem 2
 * Aiden Rader
 * 
 * EECS 2500 Linear Data Structures
 * Dr.Kishwar Ahmed
 * 01/30/2023
 */

public class ArrayBoundedStack implements StackInterface<String> 
{
  protected final int DEFCAP = 100; // default capacity
  protected String[] elements;           // holds stack elements
  protected int topIndex = -1;      // index of top element in stack

public ArrayBoundedStack() 
  {
    this.elements = new String[DEFCAP];
  }

  public void push(String element)
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

  public String top()
  // Throws StackUnderflowException if this stack is empty,
  // otherwise returns top element of this stack.
  {                 
    String topOfStack = null;
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
  
  public String poptop()
  {
	  if(topIndex==-1)
		  throw new StackUnderflowException("Top attempted on an empty stack.");
	  else
	  {
		  String topI=null;
		  topI=(String) elements[topIndex--];
		  return topI;
	  }
  }
}