import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class SortedArrayCollectionDemo
{

	public static void main(String[] args)
	{
		SortedArrayCollection<String> animal = new SortedArrayCollection<>();

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
		System.out.println("Sorted Collection: "); // Print entire collection before the change
		System.out.println(animal.toString());

		Scanner inReader = new Scanner(System.in);
		System.out.print("Enter name of animal for which you want to count number of alphabatically later animals: \r" + "\nName> ");
		String target = inReader.nextLine();

		int count = animal.greater(target);
		System.out.println("Count of animals that are alphabetically later: " + count);

		inReader.close();
	}

}
