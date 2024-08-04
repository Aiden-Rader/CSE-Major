public class Part3
{
	 static long perms; 
	 static int size; 
	 static String format = "%-11s %d permutations in %15.10f seconds (%9d permutations / second)\n";

	 public static void main(String[] args)
	 {
	 long time; 
	 double elapsed; 

	 long reps = 10;   //27000000000L for size 1
	 size = 13; 

	 long fact = 1; 
	 for (int i = size; i > 1; fact *= i--); 
	 System.out.println("Size: " + size + " (" + size + "! = " + fact + ")"); 

	 perms = 0; 
	 time = System.nanoTime(); 
	 for (int times = 1; times <= reps; times++) 
	 {
	 int[] A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	 generateRec(size, A); 
	 }
	 elapsed = ((System.nanoTime() - time) / 1000000000.0 / reps);
	 System.out.printf(format, "Recursive", perms/reps, elapsed, (long)(perms/elapsed/reps)); 
	 
	 } // end main

	 
	//Start of methods for generating using recursion
	public static void generateRec(int n, int[] A)
	{
		int temp;
		if (n == 1)
		{
			perms++;
		}
		
		else 
		 {
			for (int i = 0; i < (n-1); i++) 
			{
				generateRec(n - 1, A);
				  if (n % 2 == 0)
				  {
					  temp = A[i];
					  A[i] = A[n-1];
					  A[n-1] = temp;
				  }
				  
				  else
				  {
					  temp = A[0];
					  A[0] = A[n-1];
					  A[n-1] = temp;
				  }
			}
			generateRec(n - 1, A);
			
		 } //end if
		
	 }//end class

} // end main

