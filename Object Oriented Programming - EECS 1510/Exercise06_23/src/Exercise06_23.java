
public class Exercise06_23
{
	public static void main(String[] args) {
		
		java.util.Scanner input = new java.util.Scanner(System.in);
		System.out.print("Enter a string: ");
        String enterString = input.nextLine();
        System.out.print("Enter a character: ");
        char enterChar = input.next().charAt(0);
        
        System.out.println("The number of occurrences of " + enterChar +" in " + enterString + " " + "is" + " " + count(enterString,enterChar));
        input.close();
	}

	public static int count(String precum, char a)
	{
		int count = 0;
        for (int i = 0; i < precum.length(); i++) {

            if (precum.charAt(i) == a) count++;
        }

        return count;
	}
}
