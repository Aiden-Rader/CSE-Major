import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class ArrayCollectionDemo
{

	public static void main(String[] args)
	{
		ArrayCollection<String> animal = new ArrayCollection<>();

		try
		{
			Scanner input = new Scanner(new File("C:\\Users\\aiden\\Documents\\2500 EECS\\AnimalsPart.txt\\"));
			while (input.hasNextLine())
			{
				String name = input.nextLine();
				animal.add(name);
			}
			input.close();
		}

		catch (FileNotFoundException e)
		{
			System.out.println("File not found: " + e.getMessage());
			System.exit(0);
		}
		System.out.println("Collection: "); // Print entire collection before the change
		System.out.println(animal.toString());

		Scanner inReader = new Scanner(System.in);
		System.out.print("Enter name of animal that you want to count:\nName> ");
		String target = inReader.nextLine();
		int count = animal.count(target);
		System.out.println("The animal name " + target + " appears " + count + " times.");

		System.out.print("Enter name of animal that you want to remove:\nName> ");
		String removeTarget = inReader.nextLine();
		animal.removeAll(removeTarget);
		System.out.println("The collection after removing. \nCollection: ");
		System.out.println(animal.toString());

		inReader.close();
	}
}
