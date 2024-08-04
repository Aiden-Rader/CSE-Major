// This is the linked node class which is used for creating a new node
// in a given LinkedList, our list cases

public class LLNode<String>
{
	protected String info; // the data this node stores 
	protected LLNode link; // a link to the NEXT node 
	protected int count; 
	
	  
	  public LLNode(String info)
	  {
	    this.info = info;
	    link = null;
	    count = 0; //Making count 1 by default
	  }	  
	  
	  public String getInfo() //Getter method
	  {    
	    return info;
	  }
	  
	  public void setInfo(String info) //Setter method
	  {
	    this.info = info;
	  }
	  
	  public LLNode getNext() //Getter for getting the link node
	  {
	    return link;
	  }

	  public void setNext(LLNode link) 
	  {
	    this.link = link;
	  }
	  
	  public void increase(int num)
	  {
		count += num;
	  }

	  public int getCount()
	  {
		return count;
	  }

	public int compareTo()
	{
		// TODO Auto-generated method stub
		return 0;
	}
}
