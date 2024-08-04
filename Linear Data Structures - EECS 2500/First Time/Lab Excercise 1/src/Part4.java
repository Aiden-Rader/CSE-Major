public class Part4
{
	static long perms; 
	 static int size; 
	 static String format = "%-11s %d permutations in %15.10f seconds (%9d permutations / second)\n";

	 public static void main(String[] args)
	 {
	 long time; 
	 double elapsed; 

	 long reps = 1200000000; 
	 size = 2; 

	 long fact = 1; for (int i = size; i > 1; fact *= i--); 
	 System.out.println("Size: " + size + " (" + size + "! = " + fact + ")"); 

	 perms = 0; 
	 time = System.nanoTime(); 
	 for (int times = 1; times <= reps; times++) 
	 {
	 int[] A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	 generateNonRec(size, A); 
	 }
	 elapsed = ((System.nanoTime() - time) / 1000000000.0 / reps);
	 System.out.printf(format, "Iterative", perms/reps, elapsed, (long)(perms/elapsed/reps)); 
	 }

	public static void generateNonRec(int n, int[] A)
	{	
		 int[] C = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};	
//		int[] C = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

		int i = 1;
//		 		System.out.println(n);
		 		
			 for (i = 0; i < (n); i++) 
				{
			 		C[i] = 0;
					generateNonRec(n - 1, A);
				}

		perms++;

		while (i < n); 
		{
				 if (C[i] < i)
				 {
					  int temp; //temporary value
					  
					  if (i % 2 == 0) //if i is even, then swap A[i] and A[0]
					  {
						  temp = A[i];
						  A[i] = A[0];
						  A[0] = temp;
					  }
					  
					  else //otherwise, swap A[i] and A[c[i]]
					  {
						  temp = A[i];
						  A[i] = A[C[i]];
						  A[C[i]] = temp;
						  
					  }//end nested if else					  
					  C[i]++;
					  i = 1;
					  
				 } //end if
				 
				 else
				 {
					 C[i] = 0;
					 i++;
					 
				 } //end if
				 
		 }//end while 
//		System.out.println(A);
	}//end class
	 
} // end main
