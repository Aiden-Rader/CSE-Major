//This class is for the second list which will 
//be the "sorted" (alphabetical) list

public class List2 extends BaseList 
{
	public List2()
	{
		super(); // call BaseLists constructor to set counts to zero and make an empty list
	}
	
	@Override
	public void add(String word)
	{
		LLNode currNode = list;
		LLNode<String> prevLoc;
		LLNode<String> location;
		LLNode<String> listWord;
		
		location = list;
		prevLoc = null;
		
		while (location != null)
		{
			word = location.getInfo();
			if (listWord.compareTo(word) < 0)
			{
				prevLoc = location;
				location = location.getNext();
			}
			else
				break;
		}
		// Prepare the node for insertion
		LLNode<String> newNode = new LLNode<String>(word);
		
		if (prevLoc == null)
		{
			newNode.setNext(list);
			list = newNode;
		}
		else
		{
			newNode.setNext(location);
			prevLoc.setNext(newNode);
		}
		
//	    found = false;
//	    while (location != null)
//	    {
//	        if (location.getInfo().equals(target))
//	        {
//	          found = true;
//	          return;
//	        }
//	        else
//	        {
//	          previous = location;  // previous “lags behind” location
//	          location = location.getLink();
//	        }
//	    }
	}
	
}// End of List2
