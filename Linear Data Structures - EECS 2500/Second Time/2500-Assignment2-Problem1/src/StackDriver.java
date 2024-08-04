public class StackDriver 
{
//The main method is where our user will do the inputs
	
	public static void main(String[] args) 
	{
		ArrayBoundedStack stack = new ArrayBoundedStack();		
		
				stack.push("Lucy"); //The first item added to the stack
				System.out.println(stack);
				
				stack.push("Ricky"); //Make 3 push
				stack.push("Fred");
				stack.push("Ethel");
				System.out.println(stack);
				
				stack.pop();
				System.out.println(stack);

				stack.push("Ricky Jr.");
				System.out.println(stack);

				stack.swapStart();
				System.out.println(stack);
				
				stack.poptop(); //Pops Fred off
				System.out.println(stack);
				
				stack.popSome(2);
				System.out.println(stack);

				stack.pop();
				System.out.println(stack);
	}

}
