/* Homework Assignment #1
 * Aiden Rader
 * 
 * EECS 2500 Linear Data Structures
 * Dr.Kishwar Ahmed
 * 01/26/2023
 */

import java.text.DecimalFormat;
import java.util.Scanner;

public class ShoppingBag //Initial class
{
	private int itemsInBag;
	private double tax;
	private double totalCost;
	private double itemCost;
	
	DecimalFormat df = new DecimalFormat("$##.##"); //Make format for cost with $ and correct decimal places
	
	public ShoppingBag(double tax) //Constructor for the tax variable 
	{
	this.tax = tax;
	}
	
	public void place(int itemsInBag, double itemCost) //finding the items in a bag and the total cost
	{
	this.itemCost += itemCost;
	
	double costofItem = itemsInBag * itemCost;
	
	this.itemsInBag += itemsInBag;
	this.totalCost += costofItem;

	}
	
		public int TotalItems() //returning the total items in a bag
		{ 
		return itemsInBag;
		}

		public double RetailCost() // returning the retail cost
		{ 
		return this.totalCost;
		}

		public double TotalCost() //returning the total cost including tax
		{ 
		return ((getTax() * RetailCost() ) + RetailCost());
		}
		
		public double getTax() //getter for the tax variable
		{
		return tax;
		}
		
		public double getItemCost() //getter for the item cost
		{
			return this.itemCost;
		}
		
	public String toString() // converting the output using the toString method
		{
		return //Returns the text in the console
		"The bag contains " + TotalItems() +" items. " 
		+ "The retail cost of the items is " + df.format(RetailCost())
		+ ". The total cost of the items, including tax, is " + df.format(TotalCost())+ ".";
		}
	
final static double taxRate = 0.06; //Definitive Tax Rate set at 6%
		
	public static void main(String [] args)
	{
		Scanner scan = new Scanner(System.in); //Scanner needed for User Input
		ShoppingBag myBag = new ShoppingBag(taxRate); // Going back to the ShoppingBag class
		
		System.out.print("Enter count (use 0 to stop): "); // Ask user to input number of items.. 0 to stop
		int items = scan.nextInt();
		
		while(items!=0) //if the count is not zero, proceed with entering cost as User input.
		{
		System.out.print("Enter Cost: "); 
		double costitem = scan.nextDouble(); //User defines/inputs cost of the item
		
		myBag.place(items,costitem);
		
		System.out.print("Enter count (use 0 to stop): "); //Repeat same function as above
		items = scan.nextInt();

		}
		System.out.println(myBag.toString()); //Print out text as defined in toString method
		
		scan.close(); //closes scanner
	}

}
