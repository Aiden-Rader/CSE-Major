/*
public class sqrt
{
//version 1
	public static void main(String[] args)
	{
		// given double x, this computes √x
		   double g=2, x=1200, r; // initial guess is 2
		   	do
		   	{
		       r = x / g;        // result
		       g = (r + g) / 2;  // new guess
		       System.out.println(r);
		   	} while (Math.abs(r-g) > 1.0e-14);
		   	System.out.println(r);
		   // g now contains √x (as close as we
		   // can get with an irrational number!)


	}
}*/
	
	public class sqrt
	{
	//version 2
		public static void main(String[] args)
		{
			// given double x, this computes √x
			   double x=1200;
			   System.out.print (sqrt(x));
		}
		
		
		//Square Root Method Starts Here
		static double sqrt (double x)
		{
			double g=2, r; // initial guess is 2
			do
	   	{
		       r = x / g;        // result
		       g = (r + g) / 2;  // new guess
		     //  System.out.println(r);
		   	} while (Math.abs(r-g) > 1.0e-14);
			return r;
		   // g now contains √x (as close as we
		   // can get with an irrational number!)
		}
	}
