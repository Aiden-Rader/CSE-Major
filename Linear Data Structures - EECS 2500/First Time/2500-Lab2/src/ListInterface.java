public interface ListInterface
{
	public void add(String word); // add this word to the linked list
	
	public long getKeyCompare(); // Get the number of key comparisons
	public long getRefChanges(); // Get the number of reference changes
	
	public int getDistinctWords(); // Get the # of distinct words on the list
	public int getTotalWords(); // Get the total number of ALL words 
}

//getKeyCompare() and getRefChanges() 
//I have questions on how to implement anything