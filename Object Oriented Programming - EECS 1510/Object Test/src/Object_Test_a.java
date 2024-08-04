
public class Object_Test_a
{
	int apples;
	int bannanas;

	Object_Test_a()
	{
		this.apples = 0;
		this.bannanas = 5;
	}

	Object_Test_a(Object_Test_a a)
	{
		this.apples = a.apples;
		this.bannanas = a.bannanas;
	}

	public void increment()
	{
		this.apples++;
	}

}
//class main2
//{
//	public static void main(String args []) 
//	{
//		Object_Test_a input = new Object_Test_a();
//		
//		System.out.println(input.apples);
//		input.increment();
//		System.out.println(input.apples);
//		
//		Object_Test_a output = new Object_Test_a(input);
//		System.out.println(output.apples);
//	}
//}