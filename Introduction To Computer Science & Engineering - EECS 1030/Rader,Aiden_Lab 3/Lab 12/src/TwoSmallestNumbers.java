

/* Name: Aiden Rader
 * Date: 9-21-21
 * Instructor: Dr.Hobbs
 * Class: EECS 1030
 * Session: 004
 * Assignment: Lab 3
 * Title of Assignment: Two Smallest Numbers
 * 
 * */
import java.util.Scanner;

public class TwoSmallestNumbers {
	public static void main(String[] args) {
		Scanner scnr = new Scanner(System.in);
		
		int input = scnr.nextInt();
		int min = scnr.nextInt();
		int min2 = scnr.nextInt(); 
		int num;
		
		if (min > min2)  {
			int temp = min;
			min = min2;
			min2 = temp;
		}
		for (int i = 2; i < input; i++)  {
			num = scnr.nextInt();
			if (num < min)  {
				min2 = min;
				min = num;
			}
			else if (num < min2) {
				min2 = num;
			}
		}
		System.out.println(min + " and " + min2);
	}
}
