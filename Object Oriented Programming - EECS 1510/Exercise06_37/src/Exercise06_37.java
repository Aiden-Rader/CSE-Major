
public class Exercise06_37
{
	public static void main(String[] args)
	{
		java.util.Scanner input = new java.util.Scanner(System.in);
		System.out.print("Enter an Integer: ");
		int integer = input.nextInt();
		System.out.print("Enter the width: ");
		int width = input.nextInt();
		
		System.out.println(integer + " formatted to width " + width + ": " + format(integer, width));
		input.close();
	}

	public static String format(int integer, int width)
	{
		String num = integer + "";
		
		if(num.length() < width) 
		{
			for (int i = width - num.length(); i > 0; i--) 
			{
				num = 0 + num;
				
				
			}
		}
		return num;
	}
}
