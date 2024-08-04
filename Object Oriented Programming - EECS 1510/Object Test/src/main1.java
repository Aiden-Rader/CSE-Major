
public class main1
{
	public static void main(String args[])
	{
		Object_Test_a input = new Object_Test_a();

		System.out.println(input.apples); // input.apples=0
		input.increment(); // input.apples++
		System.out.println(input.apples); // input.apples=1
		input.increment(); // input.apples++

		Object_Test_a output = new Object_Test_a(input);
		System.out.println(input.apples);
		output.increment(); // output.apples++
		System.out.println(output.apples);
	}
}
