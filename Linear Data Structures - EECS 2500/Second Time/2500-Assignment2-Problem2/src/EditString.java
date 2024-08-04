import java.util.Scanner;

/* assume a “friendly user,” that is, the user will not enter anything illegal
 */

public class EditString 
{

	public static void main(String[] args) 
	{
		
		ArrayBoundedStack stack = new ArrayBoundedStack(); //Stores all operations
		
		Scanner scan = new Scanner(System.in);
		String userIn = scan.nextLine();
		
		String opt = " ";
		
		while(!opt.equals("X"))
		{
			opt = scan.nextLine();
			String ch[] = opt.split(" "); //This will be important when using the C command to split the two channels 
			
			if(opt.equals("U")) //make all letters uppercase
			{
				userIn = userIn.toUpperCase();
				stack.push(userIn);
			}
			else if(opt.equals("L")) //make all letter lowercase
			{
				userIn = userIn.toLowerCase();
				stack.push(userIn);
			}
			else if(opt.equals("R")) //reverse the string
			{
				StringBuilder sB = new StringBuilder(userIn); //The String builder class is an in-built class 
				userIn = sB.reverse().toString();
				stack.push(userIn);
			}
			else if(opt.length()>1 && opt.charAt(0)=='C') //change all occurrences of ch1 to ch2
			{
				userIn = userIn.replace(ch[1], ch[2]);
				stack.push(userIn);
			}
			else if(opt.equals("Z")) //Undo command
			{
				userIn = (String) stack.poptop();
				userIn = (String) stack.top();
				stack.push(userIn);
			}
		}
		System.out.print(userIn);
	}
}
