import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class ArrayCollectionDemo
{
	public static void main(String[] args)
	{
		ArrayCollection<String> animals = new ArrayCollection<>();
		try
		{
			Scanner input = new Scanner(new File("C:\\Users\\aiden\\Documents\\2500 EECS\\Animals.txt\\"));
			while (input.hasNextLine())
			{
				String name = input.nextLine();
				animals.add(name);
			}
		}

		catch (FileNotFoundException e)
		{
			System.out.println("File not found: " + e.getMessage());
			System.exit(0);
		}

		Random rand = new Random();
		char firstChar = (char) (rand.nextInt(26) + 'A'); // 26 letters of the alphabet and it chooses a random letter
		System.out.println("Enter names of animals that begins with the character: " + firstChar);

		Scanner scan = new Scanner(System.in);
		ArrayCollection<String> inputAnimal = new ArrayCollection<>();
		int count = 0;
		while (true)
		{
			System.out.print("Name> ");
			String an = scan.nextLine();
			if (an.charAt(0) != firstChar)
			{
				break;
			} 
			else if (inputAnimal.contains(an))//If that animal has already been placed on our collection then exit while loop
			{
				break;
			} 
//			else if (!animals.contains(an)) //if animals.txt DOES NOT contain the types animal then print and break out of loop
//			{
//				System.out.println(an + " is not in the animal collection.");
//			} 
			else
			{
				inputAnimal.add(an);
				count++;
			}
		}
		System.out.println("You successfully entered " + count
				+ " unique animal name(s) that begins with the character " + firstChar + ".");
		scan.close();
	}
}
