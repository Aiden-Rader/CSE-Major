
public class Exercise06_25
{
	public static void main(String[] args)
	{
		java.util.Scanner input = new java.util.Scanner(System.in);
		System.out.print("Enter time in milliseconds: ");
		long millSec = input.nextLong();
		
		System.out.println("hours:minuties:seconds: " + convertMillis(millSec));
		input.close();
	}

	public static String convertMillis(long millSec)
	{
		millSec /= 1000;
		
		String currentMinAndSec = "";
		for (int i = 0; i < 2; i++) 
		{
			
			currentMinAndSec = ":" + millSec % 60 + currentMinAndSec;
			millSec /= 60;
		}
		return millSec + currentMinAndSec;
	}
}
