/* Name: Aiden Rader
 * Date: 9-21-21
 * Instructor: Dr.Hobbs
 * Class: EECS 1030
 * Session: 004
 * Assignment: Lab 3
 * Title of Assignment: Leap Year
 * 
 * */

public class Lab10 {
	public static void main(String[] args)
	{
	Scanner scnr = new Scanner(System.in);
	      int inputYear;
	      boolean isLeapYear;
	      
	      isLeapYear = false;
	      inputYear = scnr.nextInt();
	      
	      if(inputYear % 4 == 0)  { 
	    	  
	    	  System.out.print(inputYear)  
	      	  System.out.print(" - leap year"))

	      }	 else if(inputYear % 100 == 0) {
	    	  
	    	  System.out.print(inputYear)  
	      	  System.out.print(" - leap year"))

	      }   
	      
	    	   
	 
	    	 
	      
	      scnr.close();
	}
}

/*
 * Ask for a year Calculate if the year is divisible by 4 If it is a century
 * year, it will be divisible by 400 Display if result is a leap year or not
 */

}
