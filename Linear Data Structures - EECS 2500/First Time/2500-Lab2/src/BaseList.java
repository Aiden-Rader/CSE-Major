
// This class is just a starting point for the four lists that will be used in this project.
// Because the only thing that will differentiate them is the WAY we do the additions to the
// list, we can put all of the code that's common to ALL of them here, and use inheritance 
// to build the four specific lists.  We declare this one as being abstract simply to keep 
// from accidentally instantiating it -- it doesn't HAVE its add method.
//
// By forcing this layer of inheritance into the process, every list's class just consists 
// of a one-line constructor (to call this one) which is the super() we use, and its add() method.

public abstract class BaseList implements ListInterface
{
	 LLNode list;
	 long refChanges;
	 long keyCompare;
	 
	 public BaseList() // constructor: empty list, counters set to zero
	 {
		 list = null;
		 refChanges = 0;
		 keyCompare = 0;
	 }
	 
	 @Override
	 public long getRefChanges()
	 {
	 // How many reference changes did we do (how much structural work)?
		 return refChanges;
	 }
	 
	 @Override
	 public long getKeyCompare()
	 {
	 // How many key comparisons (how much work was done looking for things on the list)
		 return keyCompare;
	 }
	 
	 @Override
	 public int getDistinctWords() //This is named "Vocabulary" on the chart
	 {
		 // How many nodes are there on the list? Each corresponds to a unique word
		 int count = 0; 
		 LLNode p = list; 
		 
	 while (p != null) 
	 { 
		 count++; 
		 p = p.getNext(); 
	 } 
	 return count; 
	 }
	 
	 @Override
	 public int getTotalWords()
	 {
		 // How many TOTAL words? That's the sum of the counts in each node.
		 int count = 0;
		 LLNode p = list;
		 
		while (p != null)
	 	{
		 count += p.getCount();
		 p = p.getNext();
	 	}
	 return count;
	 }
	 
}// End of BaseList class
