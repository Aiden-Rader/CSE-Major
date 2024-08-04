//This is the class that is for unsorted list 

public class List1 extends BaseList
{	
	public List1()
	{
		super(); // call BaseLists constructor to set counts to zero and make an empty list
	}
	
	@Override
	public void add(String word)
	// Adds element to this list, in this case we add s to the list
	{
		LLNode currNode = list;
		//Add s to the list, if s is already on the list then it just increments 
		//the count in the node containing s. If its NOT on the list, then we create a new node
		//which is added to the beginning of the list 
		while (currNode.getInfo() != null)
	
			if (currNode.getInfo() == word)
			{
				currNode.increase(1);
				return;
			}
		currNode = currNode.getNext();
			
		LLNode<String> newNode = new LLNode<String>(word); // make node
		
	} // end add

	
} // End List1 class
