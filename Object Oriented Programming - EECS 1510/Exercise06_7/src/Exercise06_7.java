/* Name: Aiden Rader
 * Date: 1-20-22
 * Instructor: Dr.Hobbs
 * Class: EECS 1520
 * Session: 001
 * Assignment: Exercise 6.7
 * Title of Assignment: Exercise 6.7
 * */
public class Exercise06_7
{
	public static void main(String[] args)
	{
		java.util.Scanner input = new java.util.Scanner(System.in);
		//hello

		// enter the loan amount
		System.out.print("Investment amount: ");
		double investmentAmount = input.nextDouble();

		// enter yearly interest
		System.out.print("Annual interest rate: ");
		double annualInterestRate = input.nextDouble();

		System.out.printf("%-5s%20s\n", "Years", "Future Value");

		for (int i = 1; i <= 50; i++)
		{
			double futureValue = futureInvestmentValue(investmentAmount, annualInterestRate / 1200, i);

			System.out.printf("%-5s%20.2f\n", i, futureValue);
			input.close();
		}
	}
	// calculate future investment(make method call)

	public static double futureInvestmentValue(double investmentAmount, double monthlyIntrestRate, int years)
	{
		return investmentAmount * Math.pow(1 + monthlyIntrestRate, years * 12);

	}
}
