
public class Exercise06_13
{
	public static void main(String[] args)
	{
		//print out a formatted table
		
		System.out.printf("%4s%20s\n", "i", "m(i)");
		
		//gonna need a for loop or some loop for the series
		
		for (int i=1; i <= 20; i++)  //starts at 1 and counts up, by 1s, until 20
	
		//need to make a method call to m
	
	System.out.printf("%4d%20.4f\n",  i,  m(i));  //creates spaces and inputs m(i) with four decimal places
	}
	
//need to write the code to calculate the series in method m
	
	public static double m(double dumb)
	{
		double sum = 0;
		
		for (double k = 1; k <= dumb; k++)
		{
			sum += k/(k+1);
		}	

return sum;
	}
}
