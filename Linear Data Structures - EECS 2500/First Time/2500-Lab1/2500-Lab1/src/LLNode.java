
public class LLNode<T>
{
	protected T info;      // the data this node stores 
	protected LLNode<T> link; // a link to the NEXT node
	  
	  public LLNode(T info)
	  {
	    this.info = info;
	    link = null;
	  }
	  public void setInfo(T info) //Setter method
	  {
	    this.info = info;
	  }

	  public T getInfo() //Getter method
	  {    
	    return info;
	  }

	  public void setLink(LLNode<T> link) 
	  {
	    this.link = link;
	  }

	  public LLNode<T> getLink() //Getter for getting the link node
	  {
	    return link;
	  }

}
