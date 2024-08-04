
public class printf_test
{

	public static void main(String[] args)
	{		
		ListInterface[] Lists = new ListInterface[4]; // By creating the lists as an array,
		 // we can iterate with a subscript
		Lists[0] = new List1(); // Unsorted, insertions at beginning, no self-optimization
		Lists[1] = new List2(); // Sorted linked list
		Lists[2] = new List3(); // Unsorted, heavy-handed self-adjusting (moves repeated
		 // word to the front of the list)
		Lists[3] = new List4(); // Unsorted, conservative self-adjusting (moves repeated
		 // word one position towards front of list)
		//
		String[] ListNames = {"Unsorted", "Sorted", "Self-Adj (Front)",
		 "Self-Adj (By One)"};

		
		System.out.printf("%2s %12s %14s %12s %12s %10s %12s", "#", "List Name", "Run Time", "Vocabulary", "Total Words", "Key Comp", "Ref Chgs");  
			System.out.println();
		System.out.println("--" + " " + "-----------------" + "  " + "--------" + "   " + "----------" + "  " + "-----------" + " " + "------------" +  " " + "------------");
						 //  #               List Name                Run Time             Vocabulary            Total Words  			 Key Comp				 Ref Chgs
		
		System.out.printf("%2s %1s ", "1", ListNames[0]); //,List1.currentTimeMillis(), List1.getDistinctWords(), List1.getTotalWords());
			System.out.println();
		
		System.out.printf("%2s %1s ", "2", ListNames[1]); //,List2.currentTimeMillis(), List2.getDistinctWords(), List2.getTotalWords());
			System.out.println();

		System.out.printf("%2s %1s ", "3", ListNames[2]); //,List3.currentTimeMillis(), List3.getDistinctWords(), List3.getTotalWords());
			System.out.println();

		System.out.printf("%2s %1s ", "4", ListNames[3]); //,List4.currentTimeMillis(), List4.getDistinctWords(), List4.getTotalWords());
			System.out.println();
	}
	
	
  
}

/*      

 # 	  List Name      Run Time  Vocabulary  Total Words   Key Comp     Ref Chgs
-- ----------------- --------  ----------  ----------- ------------ ------------
 1 Unsorted 		 9999.999    9999999   999999999   99999999999  99999999999
 2 Sorted 		   	 9999.999    9999999   999999999   99999999999  99999999999
 3 Self-Adj (Front)  9999.999    9999999   999999999   99999999999  99999999999
 4 Self-Adj (By One) 9999.999    9999999   999999999   99999999999  99999999999
 
*/

